// InfFile.cpp: implementation of the InfFile class.
//
//////////////////////////////////////////////////////////////////////

#include "InfFile.h"

#include "CFILE.H"
#include "pstring.h"
#include "pserror.h"

#include <string.h>

#define INFFILE_NULL -1024


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

InfFile::InfFile()
{
	m_fp = NULL;
}


InfFile::~InfFile()
{
// close file and free symbol lists
	Close();
}


//	symbol functions.
void InfFile::AddSymbol(const char * name, const char * text)
{
	tListNode<sym_info> *symbol = new tListNode<sym_info>;

	strcpy(symbol->t.name, name);
	symbol->t.text = new char[strlen(text)+1];
	strcpy(symbol->t.text, text);

	m_sym_list.link(symbol);
}


void InfFile::FreeSymbols()
{
	tListNode<sym_info> *sym;

	m_sym_list.start();

	while ((sym = m_sym_list.start())!=0)
	{
		sym = m_sym_list.unlink();
		if (sym->t.text) 
			delete sym->t.text;
		delete sym;
	}
}


const char* InfFile::GetSymbolText(const char * name)
{
	tListNode<sym_info> *sym;

	m_sym_list.start();
	for (sym=m_sym_list.start(); sym; sym = sym->next)
	{
		if (strcmp(sym->t.name, name) == 0) 
			return (const char *)sym->t.text;
	}

	return NULL;
}


//	opens an inf file, pass in a lexical analyzer that will return a command index.
//	tag_check is a string that must appear at the very beginning of the file.
//	lexfn is a function to match a command to a number.   num <= 0 are taken.
bool InfFile::Open(const char *filename, const char *tag_check, int (*lexfn)(const char *command))
{
	if (m_fp)
		return false;

	m_fp = cfopen(filename, "rt");
	if (!m_fp) 
		return false;

//	do tag checking.
	if (tag_check) {
		cf_ReadString(m_linetext, INFFILE_LINELEN, m_fp);
		if (strcmp(tag_check, m_linetext) != 0) {
			cfclose(m_fp);
			m_fp = NULL;
			return false;
		}
	}

//	okay we have a 'valid' inf file.
	m_lexfn = lexfn;
	m_lineptr = NULL;
	m_endptr = NULL;
	m_line = 0;

	return true;
}


//	closes the file
void InfFile::Close()
{
	if (!m_fp)
		return;

	FreeSymbols();
	m_sym_list.free();
	cfclose(m_fp);
	m_fp = NULL;
}


//	read a command line. returns false on eof.
bool InfFile::ReadLine()
{
	if (cfeof(m_fp)) 
		return false;

	cf_ReadString(m_linetext, INFFILE_LINELEN, m_fp); 

//	start line.
	m_lineptr = &m_linetext[0];
	m_endptr = m_lineptr + strlen(m_lineptr)+1;
	m_line++;

	return true;
}


//	parses a line of 'code'.  return value from the lexfn
//	a 0 for EOL (end of line).
//	-1 for error.
//	-2 for comment
int InfFile::ParseLine(char *operand, int oprlen)
{
	if (!m_lineptr) 
		return INFFILE_EOL;

//	tokenize line.
	char command[32];								// Command read from line.
	char *opr, *cmd;
	int retval = INFFILE_NULL;

	if (strlen(m_lineptr) == 0) 
		return INFFILE_EOL;

//	parse out command and operand (command=str)
//	m_lineptr = command, opr = operand, nextcmd = next lineptr.
	cmd = strtok(m_lineptr, " \t=:");
	if (cmd) 
		opr = strtok(NULL, ",;");
	else
		Int3();

//	clean out trailing and preceeding trash (tabs, spaces, etc)
	CleanupStr(command, cmd, sizeof(command));
	if (opr) 
		CleanupStr(operand, opr, oprlen);
	else 
		operand[0] = 0;

	if (strlen(command) == 0) {
		if (strlen(operand) == 0) 
			return INFFILE_EOL;
	}

//	do predefined commands
	if (command[0] == '@') 
		retval = INFFILE_COMMENT;

//	do symbolic commands.
	if (operand[0] == '#') {
		const char *sym = GetSymbolText(&operand[1]);
		if (sym) 
			strcpy(operand, sym);
		else 
			retval = INFFILE_ERROR;
	}

	if (retval == INFFILE_NULL) {
		if (command[0] == '#') {
			AddSymbol(&command[1], operand);
			retval = INFFILE_SYMBOL;
		}
		else {
		//	do command through lex analyzer. if not preprocessed.
			if (m_lexfn) 
				retval = (*m_lexfn)(command);
		}
	}

//	adjust text pointers to prepare for next read
	char *lastptr = (opr) ? opr : cmd;
	m_lineptr = lastptr + strlen(lastptr)+1;
	if (m_lineptr >= m_endptr) 
		m_lineptr = NULL;

//	end
	return retval;
}
