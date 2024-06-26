/////////////////////////////////////////////////////////////////////
// D.A.L.L.A.S. Generated Level Script - DLL Source File
// 
// Filename:	Pinball.cpp
// Version:	3
/////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "osiris_import.h"
#include "osiris_common.h"
#include "dallasfuncs.cpp"

#ifdef _MSC_VER		//Visual C++ Build
#define STDCALL		__stdcall
#define STDCALLPTR	*STDCALL
#else					//Non-Visual C++ Build
#define STDCALL __attribute__((stdcall))
#define STDCALLPTR	STDCALL*
#endif

#ifdef __cplusplus
extern "C"{
#endif
char		STDCALL InitializeDLL(tOSIRISModuleInit *func_list);
void		STDCALL ShutdownDLL(void);
int		STDCALL GetGOScriptID(char *name,ubyte is_door);
void		STDCALLPTR CreateInstance(int id);
void		STDCALL DestroyInstance(int id,void *ptr);
short	STDCALL CallInstanceEvent(int id,void *ptr,int event,tOSIRISEventInfo *data);
int		STDCALL GetTriggerScriptID(int trigger_room, int trigger_face );
int		STDCALL GetCOScriptList( int **list, int **id_list );
int		STDCALL SaveRestoreState( void *file_ptr, ubyte saving_state );
#ifdef __cplusplus
}
#endif

// =================
// Script ID Numbers
// =================
#define ID_LEVEL_0000			0x000

#define ID_CUSTOM_OBJECT_1022		0x001

#define ID_TRIGGER_0000		0x002

// ========================
// Script Class Definitions
// ========================

class BaseScript {
public:
	BaseScript();
	~BaseScript();
	virtual short CallEvent(int event, tOSIRISEventInfo *data);
};

class LevelScript_0000 : public BaseScript {
public:
	short CallEvent(int event, tOSIRISEventInfo *data);
};

class CustomObjectScript_1022 : public BaseScript {
public:
	short CallEvent(int event, tOSIRISEventInfo *data);
};

class TriggerScript_0000 : public BaseScript {
public:
	short CallEvent(int event, tOSIRISEventInfo *data);
};

// ======================
// Global Action Counters
// ======================

#define MAX_ACTION_CTR_VALUE		100000

int ScriptActionCtr_006 = 0;
int ScriptActionCtr_000 = 0;
int ScriptActionCtr_009 = 0;
int ScriptActionCtr_010 = 0;
int ScriptActionCtr_001 = 0;
int ScriptActionCtr_003 = 0;
int ScriptActionCtr_002 = 0;
int ScriptActionCtr_004 = 0;
 
// ========================================
// Function to Clear Global Action Counters
// ========================================
void ClearGlobalActionCtrs(void)
{
	ScriptActionCtr_006 = 0;
	ScriptActionCtr_000 = 0;
	ScriptActionCtr_009 = 0;
	ScriptActionCtr_010 = 0;
	ScriptActionCtr_001 = 0;
	ScriptActionCtr_003 = 0;
	ScriptActionCtr_002 = 0;
	ScriptActionCtr_004 = 0;
}
 
// ========================================
// Function to Save Global Action Counters
// ========================================
void SaveGlobalActionCtrs(void *file_ptr)
{
	File_WriteInt(ScriptActionCtr_006,file_ptr);
	File_WriteInt(ScriptActionCtr_000,file_ptr);
	File_WriteInt(ScriptActionCtr_009,file_ptr);
	File_WriteInt(ScriptActionCtr_010,file_ptr);
	File_WriteInt(ScriptActionCtr_001,file_ptr);
	File_WriteInt(ScriptActionCtr_003,file_ptr);
	File_WriteInt(ScriptActionCtr_002,file_ptr);
	File_WriteInt(ScriptActionCtr_004,file_ptr);
}
 
// ===========================================
// Function to Restore Global Action Counters
// ===========================================
void RestoreGlobalActionCtrs(void *file_ptr)
{
	ScriptActionCtr_006=File_ReadInt(file_ptr);
	ScriptActionCtr_000=File_ReadInt(file_ptr);
	ScriptActionCtr_009=File_ReadInt(file_ptr);
	ScriptActionCtr_010=File_ReadInt(file_ptr);
	ScriptActionCtr_001=File_ReadInt(file_ptr);
	ScriptActionCtr_003=File_ReadInt(file_ptr);
	ScriptActionCtr_002=File_ReadInt(file_ptr);
	ScriptActionCtr_004=File_ReadInt(file_ptr);
}
 
 
// ===============================================================
// Start of Custom Script Block - DO NOT EDIT ANYTHING BEFORE THIS
// ===============================================================
/**{CUSTOM_SCRIPT_BLOCK_START}** DO NOT EDIT! **/
 
/*
$$QUERY
Custom
i:Get the index of the tablefile entery for [s:ObjName]
qCustomGetID
Gets the tablefile index of this object name
$$END
*/
int qCustomGetID(char *name)
{
	return Obj_FindID(name);
}

/*
$$QUERY
Custom
o:Create an object of type [e:ObjectType] and ID [i:ObjectID] at object [o:ObjectDest]
qCustomCreateObjectAtObject
Creates an object of a specified type/id at the location of a specified object
$$END
*/
int qCustomCreateObjectAtObject(int type, int id, int handle)
{
	int handletype;
	int room;
	vector pos;
	matrix orient;

	if((type != OBJ_ROBOT && type != OBJ_CLUTTER && type != OBJ_BUILDING && type != OBJ_POWERUP) || (id < 0))
		return OBJECT_HANDLE_NONE;

	Obj_Value(handle, VF_GET, OBJV_I_TYPE, &handletype);
	if(handletype == OBJ_NONE)
		return OBJECT_HANDLE_NONE;

	Obj_Value(handle, VF_GET, OBJV_I_ROOMNUM, &room);
	Obj_Value(handle, VF_GET, OBJV_V_POS, &pos);
	Obj_Value(handle, VF_GET, OBJV_M_ORIENT, &orient);

	return Obj_Create(type, id, room, &pos, &orient, OBJECT_HANDLE_NONE);
}
 
/**{CUSTOM_SCRIPT_BLOCK_END}**** DO NOT EDIT! **/
// ============================================================
// End of Custom Script Block - DO NOT EDIT ANYTHING AFTER THIS
// ============================================================
 
 
// =================
// Message File Data
// =================
 
#define MAX_SCRIPT_MESSAGES	256
#define MAX_MSG_FILEBUF_LEN	1024
#define NO_MESSAGE_STRING		"*Message Not Found*"
#define INV_MSGNAME_STRING	"*Message Name Invalid*"
#define WHITESPACE_CHARS	" \t\r\n"
 
// Structure for storing a script message
typedef struct {
	char *name;			// the name of the message
	char *message;		// the actual message text
} tScriptMessage;
 
// Global storage for level script messages
tScriptMessage *message_list[MAX_SCRIPT_MESSAGES];
int num_messages;
 
// ======================
// Message File Functions
// ======================
 
// Initializes the Message List
void InitMessageList(void)
{
	for(int j=0;j<MAX_SCRIPT_MESSAGES;j++)
		message_list[j]=NULL;
	num_messages=0;
}
 
// Clear the Message List
void ClearMessageList(void)
{
	for(int j=0;j<num_messages;j++) {
		free(message_list[j]->name);
		free(message_list[j]->message);
		free(message_list[j]);
		message_list[j]=NULL;
	}
	num_messages=0;
}
 
// Adds a message to the list
int AddMessageToList(char *name, char *msg)
{
	int pos;
 
	// Make sure there is room in the list
	if(num_messages>=MAX_SCRIPT_MESSAGES) return false;
 
	// Allocate memory for this message entry
	pos=num_messages;
	message_list[pos]=(tScriptMessage *)malloc(sizeof(tScriptMessage));
	if(message_list[pos]==NULL) return false;
 
	// Allocate memory for the message name
	message_list[pos]->name=(char *)malloc(strlen(name)+1);
	if(message_list[pos]->name==NULL) {
		free(message_list[pos]);
		return false;
	}
	strcpy(message_list[pos]->name,name);
 
	// Allocate memory for the message name
	message_list[pos]->message=(char *)malloc(strlen(msg)+1);
	if(message_list[pos]->message==NULL) {
		free(message_list[pos]->name);
		free(message_list[pos]);
		return false;
	}
	strcpy(message_list[pos]->message,msg);
	num_messages++;
 
	return true;
}
 
// Removes any whitespace padding from the end of a string
void RemoveTrailingWhitespace(char *s)
{
	int last_char_pos;
 
	last_char_pos=strlen(s)-1;
	while(last_char_pos>=0 && isspace(s[last_char_pos])) {
		s[last_char_pos]='\0';
		last_char_pos--;
	}
}
 
// Returns a pointer to the first non-whitespace char in given string
char *SkipInitialWhitespace(char *s)
{
	while((*s)!='\0' && isspace(*s)) 
		s++;
 
	return(s);
}
 
// Read in the Messages
int ReadMessageFile(char *filename)
{
	void *infile;
	char filebuffer[MAX_MSG_FILEBUF_LEN+1];
	char *line, *msg_start;
	int line_num;
	bool next_msgid_found;
 
	// Try to open the file for loading
	infile=File_Open(filename,"rt");
	if (!infile) return false;
 
	line_num=0;
	next_msgid_found=true;
 
	// Clear the message list
	ClearMessageList();
 
	// Read in and parse each line of the file
	while (!File_eof(infile)) {
 
		// Clear the buffer
		strcpy(filebuffer,"");
 
		// Read in a line from the file
		File_ReadString(filebuffer, MAX_MSG_FILEBUF_LEN, infile);
		line_num++;
 
		// Remove whitespace padding at start and end of line
		RemoveTrailingWhitespace(filebuffer);
		line=SkipInitialWhitespace(filebuffer);
 
		// If line is a comment, or empty, discard it
		if(strlen(line)==0 || strncmp(line,"//",2)==0)
			continue;
 
		if(!next_msgid_found) {		// Parse out the last message ID number
 
			// Grab the first keyword, make sure it's valid
			line=strtok(line,WHITESPACE_CHARS);
			if(line==NULL) continue;
 
			// Grab the second keyword, and assign it as the next message ID
			line=strtok(NULL,WHITESPACE_CHARS);
			if(line==NULL) continue;
 
			next_msgid_found=true;
		}
		else {	// Parse line as a message line
			
			// Find the start of message, and mark it
			msg_start=strchr(line,'=');
			if(msg_start==NULL) continue;
			msg_start[0]='\0';
			msg_start++;
			
			// Add the message to the list
			AddMessageToList(line,msg_start);
		}
	}
	File_Close(infile);
 
	return true;
}
 
// Find a message
char *GetMessage(char *name)
{
	// Make sure given name is valid
	if(name==NULL) return INV_MSGNAME_STRING;
 
	// Search message list for name
	for(int j=0;j<num_messages;j++)
		if(strcmp(message_list[j]->name,name)==0) return(message_list[j]->message);
 
	// Couldn't find it
	return NO_MESSAGE_STRING;
}
 
 
//======================
// Name List Arrays     
//======================
 
#define NUM_DOOR_NAMES		1
char *Door_names[NUM_DOOR_NAMES] = {
	"ReactorDoor"
};
int Door_handles[NUM_DOOR_NAMES];
 
#define NUM_OBJECT_NAMES		9
char *Object_names[NUM_OBJECT_NAMES] = {
	"TubbsSpawn",
	"Reactor",
	"Prize1",
	"Prize2",
	"Prize3",
	"Prize4",
	"Yellow Droptarget",
	"Blue Droptarget",
	"Red Droptarget"
};
int Object_handles[NUM_OBJECT_NAMES];
 
#define NUM_ROOM_NAMES		3
char *Room_names[NUM_ROOM_NAMES] = {
	"Outhole_Death",
	"Launch_Tube",
	"Reactor Room"
};
int Room_indexes[NUM_ROOM_NAMES];
 
#define NUM_TRIGGER_NAMES		1
char *Trigger_names[NUM_TRIGGER_NAMES] = {
	"Xecute"
};
int Trigger_indexes[NUM_TRIGGER_NAMES];
int Trigger_faces[NUM_TRIGGER_NAMES];
int Trigger_rooms[NUM_TRIGGER_NAMES];
 
#define NUM_SOUND_NAMES		1
char *Sound_names[NUM_SOUND_NAMES] = {
	"IGotIt"
};
int Sound_indexes[NUM_SOUND_NAMES];
 
#define NUM_TEXTURE_NAMES		0
char **Texture_names=NULL;
int *Texture_indexes=NULL;
 
#define NUM_PATH_NAMES		1
char *Path_names[NUM_PATH_NAMES] = {
	"Robot Arcade"
};
int Path_indexes[NUM_PATH_NAMES];
 
#define NUM_MATCEN_NAMES		0
char **Matcen_names=NULL;
int *Matcen_indexes=NULL;
 
#define NUM_GOAL_NAMES		0
char **Goal_names=NULL;
int *Goal_indexes=NULL;
 
#define NUM_MESSAGE_NAMES		5
char *Message_names[NUM_MESSAGE_NAMES] = {
	"TubbsName",
	"Prize1",
	"Prize2",
	"Prize3",
	"Prize4"
};
char *Message_strings[NUM_MESSAGE_NAMES];
 
// ===============
// InitializeDLL()
// ===============
char STDCALL InitializeDLL(tOSIRISModuleInit *func_list)
{
	osicommon_Initialize((tOSIRISModuleInit *)func_list);
	if(func_list->game_checksum!=CHECKSUM)
	{ 
		mprintf(0,"Game-Checksum FAIL!!! (%ul!=%ul)\n",func_list->game_checksum,CHECKSUM);
		mprintf(0,"RECOMPILE YOUR SCRIPTS!!!\n");
		return 0;
	}
 
	ClearGlobalActionCtrs();
	dfInit();
	InitMessageList();
 
	// Build the filename of the message file
	char filename[_MAX_PATH+1];
	char english_filename[_MAX_PATH+1];
	int lang_type;
	if(func_list->script_identifier!=NULL) {
		_splitpath(func_list->script_identifier,NULL,NULL,filename,NULL);
		sprintf(english_filename,"%s.msg",filename);
		lang_type=Game_GetLanguage();
		if(lang_type==LANGUAGE_FRENCH) strcat(filename,"_FRN");
		else if(lang_type==LANGUAGE_GERMAN) strcat(filename,"_GER");
		else if(lang_type==LANGUAGE_ITALIAN) strcat(filename,"_ITN");
		else if(lang_type==LANGUAGE_SPANISH) strcat(filename,"_SPN");
		else if(lang_type==LANGUAGE_POLISH) strcat(filename,"_POL");
		strcat(filename,".msg");
	}
	else {
		strcpy(filename,"Pinball.msg");
		lang_type=LANGUAGE_ENGLISH;
	}
	if(!ReadMessageFile(filename)) {
		if(lang_type == LANGUAGE_ENGLISH) {
			mprintf(0,"ERROR: Could not load message file - %s\n",filename);
		}
		else if(!ReadMessageFile(english_filename)) {
			mprintf(0,"ERROR: Could not load message file - %s\n",english_filename);
		}
	}
 
	int j;
 
	// Do Door Index lookups
	for(j=0;j<NUM_DOOR_NAMES;j++) 
		Door_handles[j]=Scrpt_FindDoorName(Door_names[j]);
 
	// Do Object Index lookups
	for(j=0;j<NUM_OBJECT_NAMES;j++) 
		Object_handles[j]=Scrpt_FindObjectName(Object_names[j]);
 
	// Do Room Index lookups
	for(j=0;j<NUM_ROOM_NAMES;j++) 
		Room_indexes[j]=Scrpt_FindRoomName(Room_names[j]);
 
	// Do Trigger Index lookups
	for(j=0;j<NUM_TRIGGER_NAMES;j++) {
		Trigger_indexes[j]=Scrpt_FindTriggerName(Trigger_names[j]);
		Trigger_faces[j]=Scrpt_GetTriggerFace(Trigger_indexes[j]);
		Trigger_rooms[j]=Scrpt_GetTriggerRoom(Trigger_indexes[j]);
	}
 
	// Do Sound Index lookups
	for(j=0;j<NUM_SOUND_NAMES;j++) 
		Sound_indexes[j]=Scrpt_FindSoundName(Sound_names[j]);
 
	// Do Texture Index lookups
	for(j=0;j<NUM_TEXTURE_NAMES;j++) 
		Texture_indexes[j]=Scrpt_FindTextureName(Texture_names[j]);
 
	// Do Path Index lookups
	for(j=0;j<NUM_PATH_NAMES;j++) 
		Path_indexes[j]=Scrpt_FindPathName(Path_names[j]);
 
	// Do Matcen Index lookups
	for(j=0;j<NUM_MATCEN_NAMES;j++) 
		Matcen_indexes[j]=Scrpt_FindMatcenName(Matcen_names[j]);
 
	// Do Goal Index lookups
	for(j=0;j<NUM_GOAL_NAMES;j++) 
		Goal_indexes[j]=Scrpt_FindLevelGoalName(Goal_names[j]);
 
	// Do Message Name lookups
	for(j=0;j<NUM_MESSAGE_NAMES;j++) 
		Message_strings[j]=GetMessage(Message_names[j]);
 
	return 1;
}

// =============
// ShutdownDLL()
// =============
void STDCALL ShutdownDLL(void)
{
	ClearMessageList();
}

// ===============
// GetGOScriptID()
// ===============
int STDCALL GetGOScriptID(char *name,ubyte isdoor)
{
	return -1;
}

// ================
// CreateInstance()
// ================
void STDCALLPTR CreateInstance(int id)
{
	switch(id) {
		case ID_LEVEL_0000:
			return new LevelScript_0000;
			break;
		case ID_CUSTOM_OBJECT_1022:
			return new CustomObjectScript_1022;
			break;
		case ID_TRIGGER_0000:
			return new TriggerScript_0000;
			break;
		default:
			mprintf(0,"SCRIPT: Illegal ID (%d)\n",id);
			break;
	}
	return NULL;
}

// =================
// DestroyInstance()
// =================
void STDCALL DestroyInstance(int id,void *ptr)
{
	switch(id) {
		case ID_LEVEL_0000:
			delete ((LevelScript_0000 *)ptr);
		case ID_CUSTOM_OBJECT_1022:
			delete ((CustomObjectScript_1022 *)ptr);
			break;
		case ID_TRIGGER_0000:
			delete ((TriggerScript_0000 *)ptr);
			break;
		default:
			mprintf(0,"SCRIPT: Illegal ID (%d)\n",id);
			break;
	}
}

// ===================
// CallInstanceEvent()
// ===================
short STDCALL CallInstanceEvent(int id,void *ptr,int event,tOSIRISEventInfo *data)
{
	switch(id) {
		case ID_LEVEL_0000:
		case ID_CUSTOM_OBJECT_1022:
		case ID_TRIGGER_0000:
			return ((BaseScript *)ptr)->CallEvent(event,data);
			break;
		default:
			mprintf(0,"SCRIPT: Illegal ID (%d)\n",id);
			break;
	}
	return CONTINUE_CHAIN|CONTINUE_DEFAULT;
}

// ==================
// SaveRestoreState()
// ==================
int STDCALL SaveRestoreState( void *file_ptr, ubyte saving_state )
{
	return 0;
}

// ====================
// GetTriggerScriptID()
// ====================
int	STDCALL GetTriggerScriptID(int trigger_room,int trigger_face)
{
	if(trigger_room==Trigger_rooms[0] && trigger_face==Trigger_faces[0])
		return ID_TRIGGER_0000;
 
	return -1;
}

// =================
// GetCOScriptList()
// =================
int	STDCALL GetCOScriptList( int **list, int **id_list )
{
	static int cust_handle_list[1];
	static int cust_id_list[1] = { 
		ID_CUSTOM_OBJECT_1022
	};
 
	// Fill in the custom handle list
	cust_handle_list[0]=Object_handles[1];

	*list = cust_handle_list;
	*id_list = cust_id_list;

	return 1;
}

//=======================
// Script Implementation 
//=======================

BaseScript::BaseScript()
{
}

BaseScript::~BaseScript()
{
}

short BaseScript::CallEvent(int event,tOSIRISEventInfo *data)
{
	mprintf(0,"BaseScript::CallEvent()\n");
	return CONTINUE_CHAIN|CONTINUE_DEFAULT;
}

short LevelScript_0000::CallEvent(int event,tOSIRISEventInfo *data)
{
	switch(event) { 
		case EVT_SAVESTATE:
			{
				tOSIRISEVTSAVESTATE *event_data=&data->evt_savestate;
	
				SaveGlobalActionCtrs(event_data->fileptr);
				dfSave(event_data->fileptr);
#ifdef ENABLE_CUSTOM_SAVE_AND_RESTORE
				dsCustomSave(event_data->fileptr);
#endif
			}
			break;
		case EVT_RESTORESTATE:
			{
				tOSIRISEVTRESTORESTATE *event_data=&data->evt_restorestate;
	
				RestoreGlobalActionCtrs(event_data->fileptr);
				dfRestore(event_data->fileptr);
#ifdef ENABLE_CUSTOM_SAVE_AND_RESTORE
				dsCustomRestore(event_data->fileptr);
#endif
			}
			break;
		case EVT_INTERVAL:
			{
				tOSIRISEVTINTERVAL *event_data=&data->evt_interval;
 
				// Script 003: Reactor Door LOCK
				if((((qObjAnimFrame(Object_handles[6])==10.000000f) || (qObjAnimFrame(Object_handles[7])==10.000000f)) || (qObjAnimFrame(Object_handles[8])==10.000000f)) && (qRoomHasPlayer(Room_indexes[2])==false))
				{
					aDoorLockUnlock(1, Door_handles[0]);
					
					// Increment the script action counter
					if(ScriptActionCtr_003 < MAX_ACTION_CTR_VALUE) ScriptActionCtr_003++;
				}
 
				// Script 002: Reactor Door Unlock
				if((((qObjAnimFrame(Object_handles[6])!=10.000000f) && (qObjAnimFrame(Object_handles[7])!=10.000000f)) && (qObjAnimFrame(Object_handles[8])!=10.000000f)) || (qRoomHasPlayer(Room_indexes[2])==true))
				{
					aDoorLockUnlock(0, Door_handles[0]);
					
					// Increment the script action counter
					if(ScriptActionCtr_002 < MAX_ACTION_CTR_VALUE) ScriptActionCtr_002++;
				}
			}
			break;
		case EVT_LEVELSTART:
			{
				tOSIRISEVTLEVELSTART *event_data=&data->evt_levelstart;
 
				ClearGlobalActionCtrs();
				dfInit();
 
				// Script 006: Outhole Death 4 Wind
				if(1)
				{
					aRoomSetWind(Room_indexes[0], 0.001000f, -1.000000f, 0.000000f, 5.500000f);
					
					// Increment the script action counter
					if(ScriptActionCtr_006 < MAX_ACTION_CTR_VALUE) ScriptActionCtr_006++;
				}
 
				// Script 000: Launch Tube Rm 2 Wind
				if(1)
				{
					aRoomSetWind(Room_indexes[1], -0.994000f, 0.001000f, 0.104000f, 65.000000f);
					
					// Increment the script action counter
					if(ScriptActionCtr_000 < MAX_ACTION_CTR_VALUE) ScriptActionCtr_000++;
				}
 
				// Script 010: Juggs Arcade
				if(1)
				{
					aObjSaveHandle(qCustomCreateObjectAtObject(2, qCustomGetID(Message_strings[0]), Object_handles[0]), 0);
					aObjMakeInvuln(qObjSavedHandle(0), -1);
					aSetLevelTimer(0.100000f, 0);
					
					// Increment the script action counter
					if(ScriptActionCtr_010 < MAX_ACTION_CTR_VALUE) ScriptActionCtr_010++;
				}
			}
			break;
		case EVT_TIMER:
			{
				tOSIRISEVTTIMER *event_data=&data->evt_timer;
 
				// Script 004: Put tubbs on path
				if(event_data->id==0)
				{
					aAIGoalFollowPath(qObjSavedHandle(0), Path_indexes[0], 1, 2, 1, 3, 6295808, 0);
					
					// Increment the script action counter
					if(ScriptActionCtr_004 < MAX_ACTION_CTR_VALUE) ScriptActionCtr_004++;
				}
			}
			break;
	}
	return CONTINUE_CHAIN|CONTINUE_DEFAULT;
}

short CustomObjectScript_1022::CallEvent(int event,tOSIRISEventInfo *data)
{
	switch(event) { 
		case EVT_INTERVAL:
			{
				tOSIRISEVTINTERVAL *event_data=&data->evt_interval;
 
				// Script 001: Dead Reactor
				if(qObjShields(Object_handles[1])==0.000000f)
				{
					aObjSetShields(Object_handles[1], 1000.000000f);
					aStoreObjectInPositionClipboard(qCustomCreateObjectAtObject(7, qCustomGetID(Message_strings[1]), Object_handles[2]));
					aStoreObjectInPositionClipboard(qCustomCreateObjectAtObject(7, qCustomGetID(Message_strings[2]), Object_handles[3]));
					aStoreObjectInPositionClipboard(qCustomCreateObjectAtObject(7, qCustomGetID(Message_strings[3]), Object_handles[4]));
					aStoreObjectInPositionClipboard(qCustomCreateObjectAtObject(7, qCustomGetID(Message_strings[4]), Object_handles[5]));
					aSoundPlay2D(Sound_indexes[0], 1.000000f);
					aSetObjectOnFire(Object_handles[1], 5.000000f, 0.100000f);
					aObjSpark(Object_handles[1], 200.000000f, 5.000000f);
					
					// Increment the script action counter
					if(ScriptActionCtr_001 < MAX_ACTION_CTR_VALUE) ScriptActionCtr_001++;
				}
			}
			break;
	}
	return CONTINUE_CHAIN|CONTINUE_DEFAULT;
}

short TriggerScript_0000::CallEvent(int event,tOSIRISEventInfo *data)
{
	switch(event) { 
		case EVT_COLLIDE:
			{
				tOSIRISEVTCOLLIDE *event_data=&data->evt_collide;
 
				// Script 009: Outhole of Death Collision Xecution
				if(qObjIsPlayer(event_data->it_handle)==true)
				{
					aObjDestroy(event_data->it_handle);
					
					// Increment the script action counter
					if(ScriptActionCtr_009 < MAX_ACTION_CTR_VALUE) ScriptActionCtr_009++;
				}
			}
			break;
	}
	return CONTINUE_CHAIN|CONTINUE_DEFAULT;
}

 
 
/*********************************************************
Script Save Block: DO NOT TOUCH ANYTHING IN THIS BLOCK!!! 
**********************************************************
$$SCRIPT_BLOCK_START
 
VERSION		3
NEXT_ID		11
 
// UserType value blocks
$$UTYPE_VALS_START UserVar
$$UTYPE_VALS_END
 
$$UTYPE_VALS_START UserFlag
$$UTYPE_VALS_END
 
$$UTYPE_VALS_START SpewHandle
$$UTYPE_VALS_END
 
$$UTYPE_VALS_START TimerID
0:AddPath
$$UTYPE_VALS_END
 
$$UTYPE_VALS_START SavedObjectSlot
0:TubbsRobot
$$UTYPE_VALS_END
 
$$UTYPE_VALS_START GoalID
0:Juggs End
$$UTYPE_VALS_END
 
 
// Name Lists
$$DOOR_LIST_START
ReactorDoor
$$DOOR_LIST_END
 
$$OBJECT_LIST_START
TubbsSpawn
Reactor
Prize1
Prize2
Prize3
Prize4
Yellow Droptarget
Blue Droptarget
Red Droptarget
$$OBJECT_LIST_END
 
$$ROOM_LIST_START
Outhole_Death
Launch_Tube
Reactor Room
$$ROOM_LIST_END
 
$$TRIGGER_LIST_START
Xecute
$$TRIGGER_LIST_END
 
$$SOUND_LIST_START
IGotIt
$$SOUND_LIST_END
 
$$TEXTURE_LIST_START
$$TEXTURE_LIST_END
 
$$SPECNAME_LIST_START
$$SPECNAME_LIST_END
 
$$PATH_LIST_START
Robot Arcade
$$PATH_LIST_END
 
$$MATCEN_LIST_START
$$MATCEN_LIST_END
 
$$GOAL_LIST_START
$$GOAL_LIST_END
 
$$STRM_AUDIO_LIST_START
$$STRM_AUDIO_LIST_END
 
 
// Script Tree Dump
00:6:Outhole Death 4 Wind 
	$$CHILD_BLOCK_START
	01:2:0 
	02:6 
	03:0 
		$$CHILD_BLOCK_START
		05:0 
		$$CHILD_BLOCK_END
	04:0:0:0 
		$$CHILD_BLOCK_START
		08:aRoomSetWind 
			$$CHILD_BLOCK_START
			10:2:0:Room 
			10:6:0.001000:X 
			10:6:-1.000000:Y 
			10:6:0.000000:Z 
			10:6:5.500000:Speed 
			$$CHILD_BLOCK_END
		$$CHILD_BLOCK_END
	$$CHILD_BLOCK_END
00:0:Launch Tube Rm 2 Wind 
	$$CHILD_BLOCK_START
	01:2:0 
	02:6 
	03:0 
		$$CHILD_BLOCK_START
		05:0 
		$$CHILD_BLOCK_END
	04:0:0:0 
		$$CHILD_BLOCK_START
		08:aRoomSetWind 
			$$CHILD_BLOCK_START
			10:2:1:Room 
			10:6:-0.994000:X 
			10:6:0.001000:Y 
			10:6:0.104000:Z 
			10:6:65.000000:Speed 
			$$CHILD_BLOCK_END
		$$CHILD_BLOCK_END
	$$CHILD_BLOCK_END
00:9:Outhole of Death Collision Xecution 
	$$CHILD_BLOCK_START
	01:0:0 
	02:1 
	03:0 
		$$CHILD_BLOCK_START
		05:1 
			$$CHILD_BLOCK_START
			06:qObjIsPlayer:Bool 
				$$CHILD_BLOCK_START
				10:1:1:-1:Object 
				$$CHILD_BLOCK_END
			07:0:6 
			$$CHILD_BLOCK_END
		$$CHILD_BLOCK_END
	04:0:0:0 
		$$CHILD_BLOCK_START
		08:aObjDestroy 
			$$CHILD_BLOCK_START
			10:1:1:-1:Object 
			$$CHILD_BLOCK_END
		$$CHILD_BLOCK_END
	$$CHILD_BLOCK_END
00:10:Juggs Arcade 
	$$CHILD_BLOCK_START
	01:2:0 
	02:6 
	03:0 
		$$CHILD_BLOCK_START
		05:0 
		$$CHILD_BLOCK_END
	04:0:0:0 
		$$CHILD_BLOCK_START
		08:aObjSaveHandle 
			$$CHILD_BLOCK_START
			06:qCustomCreateObjectAtObject:Object 
				$$CHILD_BLOCK_START
				10:10:0:2:ObjectType 
				06:qCustomGetID:ObjectID 
					$$CHILD_BLOCK_START
					10:8:TubbsName:ObjName 
					$$CHILD_BLOCK_END
				10:1:0:0:ObjectDest 
				$$CHILD_BLOCK_END
			10:10:0:0:SavedObjectSlot 
			$$CHILD_BLOCK_END
		08:aObjMakeInvuln 
			$$CHILD_BLOCK_START
			06:qObjSavedHandle:Object 
				$$CHILD_BLOCK_START
				10:10:0:0:SavedObjectSlot 
				$$CHILD_BLOCK_END
			10:4:-1:Time 
			$$CHILD_BLOCK_END
		08:aSetLevelTimer 
			$$CHILD_BLOCK_START
			10:6:0.100000:Time 
			10:10:0:0:TimerID 
			$$CHILD_BLOCK_END
		$$CHILD_BLOCK_END
	$$CHILD_BLOCK_END
00:1:Dead Reactor 
	$$CHILD_BLOCK_START
	01:1:1 
	02:5 
	03:0 
		$$CHILD_BLOCK_START
		05:2 
			$$CHILD_BLOCK_START
			06:qObjShields:Float 
				$$CHILD_BLOCK_START
				10:1:0:1:Object 
				$$CHILD_BLOCK_END
			07:1:0 
			10:6:0.000000:Literal 
			$$CHILD_BLOCK_END
		$$CHILD_BLOCK_END
	04:0:0:0 
		$$CHILD_BLOCK_START
		08:aObjSetShields 
			$$CHILD_BLOCK_START
			10:1:0:1:Object 
			10:6:1000.000000:Shields 
			$$CHILD_BLOCK_END
		08:aStoreObjectInPositionClipboard 
			$$CHILD_BLOCK_START
			06:qCustomCreateObjectAtObject:Object 
				$$CHILD_BLOCK_START
				10:10:0:7:ObjectType 
				06:qCustomGetID:ObjectID 
					$$CHILD_BLOCK_START
					10:8:Prize1:ObjName 
					$$CHILD_BLOCK_END
				10:1:0:2:ObjectDest 
				$$CHILD_BLOCK_END
			$$CHILD_BLOCK_END
		08:aStoreObjectInPositionClipboard 
			$$CHILD_BLOCK_START
			06:qCustomCreateObjectAtObject:Object 
				$$CHILD_BLOCK_START
				10:10:0:7:ObjectType 
				06:qCustomGetID:ObjectID 
					$$CHILD_BLOCK_START
					10:8:Prize2:ObjName 
					$$CHILD_BLOCK_END
				10:1:0:3:ObjectDest 
				$$CHILD_BLOCK_END
			$$CHILD_BLOCK_END
		08:aStoreObjectInPositionClipboard 
			$$CHILD_BLOCK_START
			06:qCustomCreateObjectAtObject:Object 
				$$CHILD_BLOCK_START
				10:10:0:7:ObjectType 
				06:qCustomGetID:ObjectID 
					$$CHILD_BLOCK_START
					10:8:Prize3:ObjName 
					$$CHILD_BLOCK_END
				10:1:0:4:ObjectDest 
				$$CHILD_BLOCK_END
			$$CHILD_BLOCK_END
		08:aStoreObjectInPositionClipboard 
			$$CHILD_BLOCK_START
			06:qCustomCreateObjectAtObject:Object 
				$$CHILD_BLOCK_START
				10:10:0:7:ObjectType 
				06:qCustomGetID:ObjectID 
					$$CHILD_BLOCK_START
					10:8:Prize4:ObjName 
					$$CHILD_BLOCK_END
				10:1:0:5:ObjectDest 
				$$CHILD_BLOCK_END
			$$CHILD_BLOCK_END
		08:aSoundPlay2D 
			$$CHILD_BLOCK_START
			10:12:0:Sound 
			10:9:1.000000:Volume 
			$$CHILD_BLOCK_END
		08:aSetObjectOnFire 
			$$CHILD_BLOCK_START
			10:1:0:1:Object 
			10:6:5.000000:Seconds 
			10:6:0.100000:Damage 
			$$CHILD_BLOCK_END
		08:aObjSpark 
			$$CHILD_BLOCK_START
			10:1:0:1:Object 
			10:6:200.000000:SparkRate 
			10:6:5.000000:Time 
			$$CHILD_BLOCK_END
		$$CHILD_BLOCK_END
	$$CHILD_BLOCK_END
00:3:Reactor Door LOCK 
	$$CHILD_BLOCK_START
	01:2:0 
	02:5 
	03:0 
		$$CHILD_BLOCK_START
		09:0 
			$$CHILD_BLOCK_START
			09:1 
				$$CHILD_BLOCK_START
				09:1 
					$$CHILD_BLOCK_START
					05:2 
						$$CHILD_BLOCK_START
						06:qObjAnimFrame:Float 
							$$CHILD_BLOCK_START
							10:1:0:6:Object 
							$$CHILD_BLOCK_END
						07:1:0 
						10:6:10.000000:Literal 
						$$CHILD_BLOCK_END
					05:2 
						$$CHILD_BLOCK_START
						06:qObjAnimFrame:Float 
							$$CHILD_BLOCK_START
							10:1:0:7:Object 
							$$CHILD_BLOCK_END
						07:1:0 
						10:6:10.000000:Literal 
						$$CHILD_BLOCK_END
					$$CHILD_BLOCK_END
				05:2 
					$$CHILD_BLOCK_START
					06:qObjAnimFrame:Float 
						$$CHILD_BLOCK_START
						10:1:0:8:Object 
						$$CHILD_BLOCK_END
					07:1:0 
					10:6:10.000000:Literal 
					$$CHILD_BLOCK_END
				$$CHILD_BLOCK_END
			05:1 
				$$CHILD_BLOCK_START
				06:qRoomHasPlayer:Bool 
					$$CHILD_BLOCK_START
					10:2:2:Room 
					$$CHILD_BLOCK_END
				07:0:7 
				$$CHILD_BLOCK_END
			$$CHILD_BLOCK_END
		$$CHILD_BLOCK_END
	04:0:0:0 
		$$CHILD_BLOCK_START
		08:aDoorLockUnlock 
			$$CHILD_BLOCK_START
			10:10:0:1:Lock/Unlock 
			10:0:0:0:DoorName 
			$$CHILD_BLOCK_END
		$$CHILD_BLOCK_END
	$$CHILD_BLOCK_END
00:2:Reactor Door Unlock 
	$$CHILD_BLOCK_START
	01:2:0 
	02:5 
	03:0 
		$$CHILD_BLOCK_START
		09:1 
			$$CHILD_BLOCK_START
			09:0 
				$$CHILD_BLOCK_START
				09:0 
					$$CHILD_BLOCK_START
					05:2 
						$$CHILD_BLOCK_START
						06:qObjAnimFrame:Float 
							$$CHILD_BLOCK_START
							10:1:0:6:Object 
							$$CHILD_BLOCK_END
						07:1:1 
						10:6:10.000000:Literal 
						$$CHILD_BLOCK_END
					05:2 
						$$CHILD_BLOCK_START
						06:qObjAnimFrame:Float 
							$$CHILD_BLOCK_START
							10:1:0:7:Object 
							$$CHILD_BLOCK_END
						07:1:1 
						10:6:10.000000:Literal 
						$$CHILD_BLOCK_END
					$$CHILD_BLOCK_END
				05:2 
					$$CHILD_BLOCK_START
					06:qObjAnimFrame:Float 
						$$CHILD_BLOCK_START
						10:1:0:8:Object 
						$$CHILD_BLOCK_END
					07:1:1 
					10:6:10.000000:Literal 
					$$CHILD_BLOCK_END
				$$CHILD_BLOCK_END
			05:1 
				$$CHILD_BLOCK_START
				06:qRoomHasPlayer:Bool 
					$$CHILD_BLOCK_START
					10:2:2:Room 
					$$CHILD_BLOCK_END
				07:0:6 
				$$CHILD_BLOCK_END
			$$CHILD_BLOCK_END
		$$CHILD_BLOCK_END
	04:0:0:0 
		$$CHILD_BLOCK_START
		08:aDoorLockUnlock 
			$$CHILD_BLOCK_START
			10:10:0:0:Lock/Unlock 
			10:0:0:0:DoorName 
			$$CHILD_BLOCK_END
		$$CHILD_BLOCK_END
	$$CHILD_BLOCK_END
00:4:Put tubbs on path 
	$$CHILD_BLOCK_START
	01:2:0 
	02:9 
	03:0 
		$$CHILD_BLOCK_START
		05:2 
			$$CHILD_BLOCK_START
			10:10:2:0:TimerID 
			07:1:0 
			10:10:0:0:TimerID 
			$$CHILD_BLOCK_END
		$$CHILD_BLOCK_END
	04:0:0:0 
		$$CHILD_BLOCK_START
		08:aAIGoalFollowPath 
			$$CHILD_BLOCK_START
			06:qObjSavedHandle:Object 
				$$CHILD_BLOCK_START
				10:10:0:0:SavedObjectSlot 
				$$CHILD_BLOCK_END
			10:16:0:Path 
			10:4:1:FirstNode 
			10:4:2:LastNode 
			10:4:1:StartNode 
			10:10:0:3:GoalPriority 
			10:15:6295808:AIGoalFlags 
			10:10:0:0:GoalID 
			$$CHILD_BLOCK_END
		$$CHILD_BLOCK_END
	$$CHILD_BLOCK_END
 
$$SCRIPT_BLOCK_END
*********************************************************/
