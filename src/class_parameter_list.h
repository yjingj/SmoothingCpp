#ifndef __PARAMETER_LIST_H__
#define __PARAMETER_LIST_H__

#if defined(_WIN32) || defined(_WIN64) 
#define snprintf _snprintf 
#define vsnprintf _vsnprintf 
#define strcasecmp _stricmp 
#define strncasecmp _strnicmp 
#endif


const int Parameter_NameLength = 100;
const int Parameter_ValueLength = 100;

const char EndOfFileMark[] = "//";
const char CommonFileMark[] = "Common_File";
const char PrintParamMark[] = "Print_Parameters";
const char PrintParamConfirmation[] = "YES";

struct Parameter
{
   char Name[Parameter_NameLength];
   char Value[Parameter_ValueLength];
   Parameter *Next;
};

typedef Parameter * PList_Element;

class ParameterListClass
{
private:
   PList_Element PL_First_Element;
   int PList_Length;

   char * LookUpParameterValue(const char * ParName);
   int ReadListFromFile(const char * filename, PList_Element & Mount_Point);

   char * common_file_name;

public:
   ParameterListClass();
   ~ParameterListClass();

   int DeleteCurrentList();

   int ReadParameters(char * filename);
   int AddParameters(char * filename);

   int LookupParameter(char * ParName, int * ParValue);
   int LookupParameter(char * ParName, double * ParValue);
   int LookupParameter(char * ParName, char * ParValue);

   void Print_Parameter_List();
};

/*
Constructor
*/

ParameterListClass :: ParameterListClass()
{
   PL_First_Element = NULL;
   PList_Length = 0;
}

/*
Desructor
*/

ParameterListClass :: ~ParameterListClass()
{
   DeleteCurrentList();
}


// ========================================================================
// ========================================================================
/*
Function DeleteCurrentList() - Deletes Current List of Parameters.
Returned Values:
   0 - list was deleted without errors;
  -1 - list was shorter than it should be;
  -2 - list is longer than it should be.
*/
// ========================================================================
// ========================================================================
int ParameterListClass :: DeleteCurrentList()
{
   PList_Element CurElement;
   int Result;

   for(int i = 0; i <= PList_Length - 1; i++)
   {
      CurElement = PL_First_Element;

      if(CurElement == NULL)
      {
         Result = -1;
         cout << "ParameterList: Deleting error - list is too short!" << endl;
         break;
      }

      PL_First_Element = PL_First_Element -> Next;
      delete CurElement;
   }

   if(PL_First_Element != NULL)
   {
      Result = -2;
      cout << "ParameterList: Deleting error - list is too long!" << endl;
   }
   else
      Result = 0;

   PList_Length = 0;
   return Result;
}

// ========================================================================
// ========================================================================
/*
Function LookUpParameterValue - Searches for a value of parameter with a specified name.
Returned Values:
   NULL - parameter with a given name is not present in the list;
   char * - pointer to a string containg parameter's value.
*/
// ========================================================================
// ========================================================================
char * ParameterListClass :: LookUpParameterValue(const char * ParName)
{
   PList_Element SoughtParameter;
   char * Result;

   if(!PList_Length)
   {
      cout << "ParameterList: Looking up error - list is empty!" << endl;
      return NULL;
   }

   SoughtParameter = PL_First_Element;
   for(int i = 0; i <= PList_Length - 1; i++)
   {
      if(!strcasecmp(SoughtParameter -> Name, ParName))
         break;

      SoughtParameter = SoughtParameter -> Next;
   }

   if(SoughtParameter != NULL)
      Result = SoughtParameter -> Value;
   else
      Result = NULL;

   return Result;
}

// ========================================================================
// ========================================================================
/*
Function LookUpParameter - Searches for an integer parameter's value.
Returned Values:
   0 - value was read succesfully ;
  -1 - parameter with a given name is not present in the list.
*/
// ========================================================================
// ========================================================================
int ParameterListClass :: LookupParameter(char * ParName, int * ParValue)
{
   char * SoughtValue;
   int Result;

   SoughtValue = LookUpParameterValue(ParName);
   if(SoughtValue != NULL)
   {
      sscanf_s(SoughtValue, "%i", ParValue);
      Result = 0;
   }
   else
      Result = -1;

   return Result;
}
// ========================================================================
// ========================================================================
/*
Function LookUpParameter - Searches for a double parameter's value.
Returned Values:
   0 - value was read succesfully ;
  -1 - parameter with a given name is not present in the list.
*/
// ========================================================================
// ========================================================================
int ParameterListClass :: LookupParameter(char * ParName, double * ParValue)
{
   char * SoughtValue;
   int Result;

   SoughtValue = LookUpParameterValue(ParName);
   if(SoughtValue != NULL)
   {
      sscanf_s(SoughtValue, "%le", ParValue);
      Result = 0;
   }
   else
      Result = -1;

   return Result;
}

// ========================================================================
// ========================================================================
/*
Function LookUpParameter - Searches for a string parameter's value.
Returned Values:
   0 - value was read succesfully ;
  -1 - parameter with a given name is not present in the list.
*/
// ========================================================================
// ========================================================================
int ParameterListClass :: LookupParameter(char * ParName, char * ParValue)
{
   char * SoughtValue;
   int Result;

   SoughtValue = LookUpParameterValue(ParName);
   if(SoughtValue != NULL)
   {
      strcpy_s(ParValue, 100, SoughtValue);
      Result = 0;
   }
   else
      Result = -1;

   return Result;
}

// ========================================================================
// ========================================================================
/*
Function ReadListFromFile - Reads and mounts new parameters to the specified point in list.
Returned Values:
   0 - parameters were read without errors;
  -1 - failed to open file with parameters;
  -2 - file had an illegal ending.
*/
// ========================================================================
// ========================================================================
int ParameterListClass :: ReadListFromFile(const char * filename, PList_Element & Mount_Point)
{
   ifstream InputFile;
   char CurName[Parameter_NameLength];
   char CurValue[Parameter_ValueLength];
   PList_Element CurParameter;
   PList_Element PrevParameter;
   int Result;

   InputFile.open(filename, ios::in);
   if(InputFile.fail())
   {
      cout << "ParameterList: Failed to open file " << filename << "!" << endl;
      return -1;
   }
   else
      cout << "ParameterList: Started reading parameters from file " << filename << "..." << endl;

   PrevParameter = Mount_Point;

   while(!InputFile.eof())
   {
      InputFile >> CurName >> CurValue;



      if(!strcmp(CurName, EndOfFileMark))
      {
         cout << "ParameterList: Completed reading parameters from file " << filename << "..." << endl;
         Result = 0;
         break;
      }

      if(InputFile.fail())
      {
         cout << "ParameterList: Illegal file ending - reading stopped!" << endl;
         Result = -2;
         break;
      }

      PList_Length++;

      CurParameter = new Parameter;
      strcpy_s(CurParameter->Name, 100, CurName);
      strcpy_s(CurParameter->Value, 100, CurValue);

      if(PrevParameter == NULL)
         Mount_Point = CurParameter;
      else
         PrevParameter -> Next = CurParameter;

      PrevParameter = CurParameter;

      //cout << "ParameterList: Parameter " << CurName << " with value " << CurValue << " has been added to list..." << endl;
   }

   InputFile.close();
   cout << "ParameterList: Currently there are " << PList_Length << " parameters in list..." << endl;

   return Result;
}


// ========================================================================
// ========================================================================
/*
Function AddParameters - Adds parameters from file to the end of list.
Returned Values:
   0 - parameters were added without errors;
  -1 - initial list was empty;
  -2 - parameters were read with errors.
*/
// ========================================================================
// ========================================================================
int ParameterListClass :: AddParameters(char * filename)
{
   PList_Element LastParameter;
   int Result;

   if(!PList_Length)
   {
      cout << "ParameterList: Error - attempt to add parameters to an empty list!" << endl;
      return -1;
   }

   LastParameter = PL_First_Element;
   for(int i = 0; i <= PList_Length - 2; i++)
      LastParameter = LastParameter -> Next;

   if(ReadListFromFile(filename, LastParameter))
      Result = -2;
   else
      Result = 0;

   return Result;
}


// ========================================================================
// ========================================================================
/*
Function ReadParameters - Reads parameters from file to a new list.
Returned Values:
   0 - parameters were read without errors;
  -1 - there were errors while cleaning up previous list;
  -2 - there were errors while reading parameter from a given file;
  -3 - there were errors while reading parameters from a Common File.
*/
// ========================================================================
// ========================================================================
int ParameterListClass :: ReadParameters(char * filename)
{
   char * CommonFileName;

   if(PList_Length)
      if(DeleteCurrentList())
         return -1;

   if(ReadListFromFile(filename, PL_First_Element))
      return -2;

   CommonFileName = LookUpParameterValue(CommonFileMark);

   if(CommonFileName != NULL)
   {
      cout << "ParameterList: Using Common File " << CommonFileName << "..." << endl;
      if(AddParameters(CommonFileName))
         return -3;
   }

   return 0;
}


// ========================================================================
// ========================================================================
/*
Procedure Print_Parameter_List - Prints current list of parameters if requested from parameters file.
*/
// ========================================================================
// ========================================================================
void ParameterListClass :: Print_Parameter_List()
{
   PList_Element CurParameter;
   char * PrintParamValue;

   if(LookUpParameterValue(PrintParamMark) == NULL) return;

   if(strcasecmp(LookUpParameterValue(PrintParamMark), PrintParamConfirmation))
      return;

   CurParameter = PL_First_Element;

   cout << "PARAMETER LIST:" << endl;

   for(int i = 0; i <= PList_Length - 1; i++)
   {
      cout << CurParameter -> Name << "    " << CurParameter -> Value << endl;
      CurParameter = CurParameter -> Next;
   }

   cout << endl;
}

#endif
