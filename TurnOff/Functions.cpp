#include "Functions.h"
#include <string>
#include <exception>

PHKEY Register_Create(HKEY machine, LPCTSTR key)
{
	PHKEY handle = new HKEY;
	DWORD err;
	if ((err = RegCreateKeyEx(machine, key, NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, handle, NULL)) == ERROR_SUCCESS)
		return handle;
	else
		throw std::exception(("Could not create key. Error " + std::to_string(err)).c_str());
}

PHKEY Register_Open(HKEY machine, LPCTSTR key)
{
	PHKEY handle = new HKEY;
	DWORD err;
	if ((err = RegOpenKeyEx(machine, key, NULL, KEY_SET_VALUE | KEY_QUERY_VALUE, handle)) == ERROR_SUCCESS)
		return handle;
	else
		throw std::exception(("Could not open key. Error " + std::to_string(err)).c_str());
}

DWORD Register_GetDWORD(HKEY machine, LPCTSTR valName)
{
	DWORD result, size = sizeof(DWORD), type = REG_DWORD;
	DWORD err = RegQueryValueEx(machine, valName, NULL, &type, (LPBYTE)&result, &size);
	switch (err)
	{
	case ERROR_SUCCESS:
		return result;
		break;
	case ERROR_FILE_NOT_FOUND:
		return -1;
		break;
	default:
		throw std::exception(("Could not query value from registry. Error " + std::to_string(err)).c_str());
		break;
	}
}

char * Register_GetSTR(HKEY machine, LPCTSTR valName, LPCTSTR keyPath)
{
	DWORD size;
	RegGetValue(machine, keyPath, valName, RRF_RT_REG_SZ, NULL, NULL, &size);
	char* value = new char[size];
	RegGetValue(machine, keyPath, valName, RRF_RT_REG_SZ, NULL, value, &size);
	return value;
}

void Register_SetValue(HKEY machine, LPCTSTR valName, DWORD type, LPCBYTE value)
{
	DWORD err;
	if (type == REG_DWORD)
	{
		if ((err = RegSetValueEx(machine, valName, NULL, REG_DWORD, value, sizeof(DWORD))) != ERROR_SUCCESS)
			throw std::exception(("Could not set value. Error " + std::to_string(err)).c_str());
	}
	else
	{
		if ((err = RegSetValueEx(machine, valName, NULL, REG_SZ, value, strlen((char*)value))) != ERROR_SUCCESS)
			throw std::exception(("Could not set value. Error " + std::to_string(err)).c_str());
	}
}

bool Register_DelValue(HKEY machine, LPCTSTR valName, LPCTSTR keyPath)
{
	DWORD err = RegDeleteKeyValue(machine, keyPath, valName);
	switch (err)
	{
	case ERROR_SUCCESS:
		return true;
	case ERROR_FILE_NOT_FOUND:
		return false;
	default:
		throw std::exception(("Could not delete key. Error" + std::to_string(err)).c_str());
	}
}

bool Regedit(HKEY machine, LPCTSTR keyPath, LPCTSTR valName, DWORD type, LPCBYTE value)
{
	bool retValue;

	//open the registry key
	PHKEY handle;
	try
	{
		handle = Register_Open(machine, keyPath);
	}
	catch (const std::exception&)
	{
		handle = Register_Create(machine, keyPath);
	}

	//check what we're dealing with. Treat 2 cases: DWORD and string
	if (type == REG_DWORD)
	{
		//check if we need to change the value, or it is already how we want it. This is for feedback
		DWORD currVal = Register_GetDWORD(*handle, valName);
		if (currVal != DWORD(*value) || currVal == -1)
		{
			Register_SetValue(*handle, valName, type, value);
			retValue = true;
		}
		else
		{
			retValue = false;
		}
	}
	else
	{
		//get the value that is already in the register
		char* val = Register_GetSTR(*handle, valName);
		if (strcmp(val, (char*)value) != 0)
		{
			Register_SetValue(*handle, valName, type, value);
			retValue = true;
		}
		else
		{
			retValue = false;
		}
	}
	RegCloseKey(*handle);
	return retValue;
}

void ServiceEdit(LPCSTR svcName, DWORD startTime)
{
	SC_HANDLE scm, sch;
	if ((scm = OpenSCManager(NULL, NULL, SERVICE_CHANGE_CONFIG)) == NULL)
		throw std::exception("Could not open Service Manager");
	if ((sch = OpenService(scm, svcName, SERVICE_CHANGE_CONFIG)) == NULL)
		throw std::exception("Could not open service");
	if (ChangeServiceConfig(sch, SERVICE_NO_CHANGE, startTime, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL) == NULL)
		throw std::exception("Could not change service start time");
	CloseServiceHandle(sch);
	CloseServiceHandle(scm);
}
