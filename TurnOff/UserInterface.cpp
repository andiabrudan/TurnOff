#include "UserInterface.h"
#include "Functions.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

template<typename Out>
void split(const std::string &s, char delim, Out result) {
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		*(result++) = item;
	}
}

std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, std::back_inserter(elems));
	return elems;
}

void Uninstall()
{
	system(BUILDER3D);							//#1
	cout << "uninstalled 3D Builder\n";
	system(GETOFFICE);							//#2
	cout << "uninstalled Get Office\n";
	system(GETSKYPE);							//#3
	cout << "uninstalled Get Skype\n";
	system(GROOVEMUSIC);						//#4
	cout << "uninstalled Groove Music\n";
	system(MAPS_WIN);							//#5
	cout << "uninstalled Windows Maps\n";
	system(SOLITAIRE);							//#6
	cout << "uninstalled Solitaire\n";
	system(VIDEO);								//#7
	cout << "uninstalled Movies & TV\n";
	system(PEOPLE);								//#8
	cout << "uninstalled People\n";
	//system(STORE);								//#9
	//cout << "uninstalled Store\n";
	system(RECORDER);							//#10
	cout << "uninstalled Voice Recorder\n";
	system(WEATHER);							//#11
	cout << "uninstalled Weather\n";
	//system(XBOX_APP);							//#12
	//cout << "uninstalled Xbox\n";
	system(NEWS_APP);							//#13
	cout << "uninstalled Bing News\n";
	system(MAIL_APP);							//#14
	cout << "uninstalled Bing News\n";
	system(CANDY_CRUSH);						//#15
	cout << "uninstalled Candy Crush\n";
	system(SKETCHBOOK);							//#16
	cout << "uninstalled Sketchbook\n";
	system(FEEDBACKHUB);						//#17
	cout << "uninstalled Feedback Hub\n";
	system(VIEWER3D);							//#18
	cout << "uninstalled 3D Viewer\n";
}

void Settings()
{
	std::stringstream success_messages;
	std::stringstream error_messages;

	DWORD zero = 0, one = 1, two = 2;

#pragma region Quality of life

#pragma region Open explorer to "this PC" instead "Quick Access"
	//open Windows Explorer to "this PC" instead of "Quick Access"
	try
	{
		if (Regedit(HKEY_CURRENT_USER, EXPLORER_REGISTER_PATH, EXPLORER_THISPC, REG_DWORD, (BYTE*)& one))
			success_messages << "Explorer now opens to \"This PC\"\n";
	}
	catch (const std::exception& e)
	{
		error_messages << e.what() << " --- this happened while changing windows explorer to open to \"This PC\"\n";
	}
#pragma endregion

#pragma region Dont group taskbar
	//don't group taskbar
	try
	{
		if (Regedit(HKEY_CURRENT_USER, EXPLORER_REGISTER_PATH, TASKBAR_NOGROUP, REG_DWORD, (BYTE*)& two))
			success_messages << "Items in taskbar no longer group\n";
	}
	catch (const std::exception& e)
	{
		error_messages << e.what() << " --- this happened while disabling taskbar grouping\n";
	}
#pragma endregion

#pragma region Dont hide folders
	//don't hide folders
	try
	{
		if (Regedit(HKEY_CURRENT_USER, EXPLORER_REGISTER_PATH, HIDE_FOLDERS, REG_DWORD, (BYTE*)& one))
			success_messages << "Now showing hidden folders\n";
	}
	catch (const std::exception& e)
	{
		error_messages << e.what() << " --- this happened while enabling \"show hidden folders\"\n";
	}
#pragma endregion

#pragma region Dont hide extensions
	//don't hide extensions
	try
	{
		if (Regedit(HKEY_CURRENT_USER, EXPLORER_REGISTER_PATH, HIDE_EXTENSIONS, REG_DWORD, (BYTE*)& zero))
			success_messages << "Now showing hidden extensions\n";
	}
	catch (const std::exception& e)
	{
		error_messages << e.what() << " --- this happened while enabling \"show file extensions\"\n";
	}
#pragma endregion

#pragma region Dont show taskview button
	//don't show taskview button
	try
	{
		if (Regedit(HKEY_CURRENT_USER, EXPLORER_REGISTER_PATH, TASKVIEW_BUTTON, REG_DWORD, (BYTE*)& zero))
			success_messages << "Taskview button hidden\n";
	}
	catch (const std::exception& e)
	{
		error_messages << e.what() << " --- this happened while disabling taskview button\n";
	}
#pragma endregion

#pragma region Change date-time format
	//change date-time format from M / D / YYYY to DD - MMM - YY
	{
		unsigned char temp1[] = "-";
		unsigned char temp2[] = "dd-MMM-yy";
		try
		{
			if (Regedit(HKEY_CURRENT_USER, DATETIME_PATH, DATETIME_NAME1, REG_DWORD, (BYTE*)& one))
				if (Regedit(HKEY_CURRENT_USER, DATETIME_PATH, DATETIME_NAME2, REG_SZ, temp1))
					if (Regedit(HKEY_CURRENT_USER, DATETIME_PATH, DATETIME_NAME3, REG_SZ, temp2))
						success_messages << "Changed date-time display format\n";
		}
		catch (const std::exception& e)
		{
			error_messages << e.what() << " --- this happened while changing date-time format\n";
		}
	}
#pragma endregion

#pragma region No search bar
	try
	{
		if (Regedit(HKEY_CURRENT_USER, SEARCH_BAR_PATH, SEARCH_BAR, REG_DWORD, (BYTE*)& zero))
			success_messages << "Search bar no longer visible on task bar\n";
	}
	catch (const std::exception& e)
	{
		error_messages << e.what() << " --- this happened while diabling Search bar\n";
	}
#pragma endregion

#pragma region Speed up taskbar preview
	//speed up taskbar preview
	try
	{
		DWORD speed = 150;
		if (Regedit(HKEY_CURRENT_USER, EXPLORER_REGISTER_PATH, TASKBARSPEED_NAME, REG_DWORD, (BYTE*)& speed))
			success_messages << "Taskbar Preview Speed now set to 150 ms (default is 400 ms)\n";
	}
	catch (const std::exception& e)
	{
		error_messages << e.what() << " --- this happened while changin the speed of taskbar preview\n";
	}
#pragma endregion

#pragma region Add notepad to right click
	//notepad add-on to right click
	{
		unsigned char temp[] = NOTEPAD_EXEC;
		try
		{
			if (Regedit(HKEY_CLASSES_ROOT, NOTEPAD_ADDON, NULL, REG_SZ, temp))
				success_messages << "Added notepad addon\n";
		}
		catch (const std::exception& e)
		{
			error_messages << e.what() << " --- this happened while adding notepad addon\n";
		}
	}
#pragma endregion


#pragma endregion

#pragma region Performance

#pragma region Disable Windows Defender
	//disable Windows Defender
	try
	{
		if (Regedit(HKEY_LOCAL_MACHINE, DEFENDER_REGISTER_PATH, DEFENDER_NAME, REG_DWORD, (BYTE*)&one))
			success_messages << "Windows Defender disabled successfully\n";
	}
	catch (const std::exception& e)
	{
		error_messages << e.what() << " --- this happened while disabling windows defender\n";
	}
#pragma endregion

#pragma region No Windows Defender tray icon
	//delete Window Defender tray icon from startup
	try
	{
		if (Register_DelValue(HKEY_LOCAL_MACHINE, DEFENDER_ICON, DEFENDER_ICON_PATH))
			success_messages << "Defender tray icon disabled\n";
	}
	catch (const std::exception& e)
	{
		error_messages << e.what() << " --- this happened while disabling windows defender tray icon\n";
	}
#pragma endregion

#pragma region Disable Telemetry
	//disable Telemetry
	try
	{
		if (Regedit(HKEY_LOCAL_MACHINE, TELEMETRY_REGISTER_PATH, TELEMETRY_NAME, REG_DWORD, (BYTE*)& zero))
			success_messages << "Telemetry disabled successfully\n";
	}
	catch (const std::exception& e)
	{
		error_messages << e.what() << " --- this happened while disabling telemetry\n";
	}
	try
	{
		ServiceEdit(SERVICE_TELEMETRY1, SERVICE_DISABLED);
		success_messages << "dmwappushsvc disabled successfully\n";
	}
	catch (const std::exception& e)
	{
		error_messages << e.what() << " --- this happened while disabling dmwappushsvc\n";
	}
#pragma endregion



#pragma region Disable Firewall
	try
	{
		if (Regedit(HKEY_LOCAL_MACHINE, FIREWALL_PATH1, FIREWALL_NAME, REG_DWORD, (BYTE*)& zero))
			if (Regedit(HKEY_LOCAL_MACHINE, FIREWALL_PATH2, FIREWALL_NAME, REG_DWORD, (BYTE*)& zero))
				success_messages << "Firewall disabled successfully\n";
	}
	catch (const std::exception& e)
	{
		error_messages << e.what() << " --- this happened while disabling firewall\n";
	}
#pragma endregion

#pragma region Disable onedrive at startup
	//disable onedrive
	try
	{
		if (Register_DelValue(HKEY_CURRENT_USER, ONEDRIVE_NAME, ONEDRIVE_REGISTRY_PATH))
			success_messages << "OneDrive no longer runs at startup\n";
	}
	catch (const std::exception& e)
	{
		error_messages << e.what() << " --- this happened while disabling OneDrive\n";
	}
#pragma endregion

#pragma endregion

#pragma region Adware

#pragma region Disable Ads
	//disable Ads
	try
	{
		success_messages << "Disabling ads:\n";
		if (Regedit(HKEY_LOCAL_MACHINE, ADS_REGISTER_PATH, ADS_NAME, REG_DWORD, (BYTE*)& one))
			success_messages << "\t-> Disable Windows Consumer Features *success*\n";
		if (Regedit(HKEY_CURRENT_USER, ADVERTISING_INFO_PATH, ADS_INFO_NAME, REG_DWORD, (BYTE*)& zero))
			success_messages << "\t-> Disable Advertising Info *success*\n";
		if (Regedit(HKEY_CURRENT_USER, SOFTLANDING_PATH, SOFTLANDING_NAME, REG_DWORD, (BYTE*)& zero))
			success_messages << "\t-> Disabled softlanding *success*\n";
	}
	catch (const std::exception& e)
	{
		error_messages << e.what() << " --- this happened while disabling ads\n";
	}
#pragma endregion

#pragma region Disable Cortana
	//disable Cortana
	try
	{
		if (Regedit(HKEY_LOCAL_MACHINE, CORTANA_REGISTER_PATH, CORTANA_NAME, REG_DWORD, (BYTE*)& zero))
			success_messages << "Cortana disabled successfully\n";
	}
	catch (const std::exception& e)
	{
		error_messages << e.what() << " --- this happened while disabling cortana\n";
	}
#pragma endregion

#pragma region Turn off Silent Install
	//disable Silent Install
	try
	{
		if (Regedit(HKEY_CURRENT_USER, SILENT_INSTALL_PATH, SILENT_NAME, REG_DWORD, (BYTE*)& zero))
			success_messages << "Silent Install disabled successfully\n";
		if (Regedit(HKEY_CURRENT_USER, SILENT_INSTALL_PATH, DELIVERY_NAME, REG_DWORD, (BYTE*)& zero))
			success_messages << "Content Delivery disabled successfully\n";
		if (Regedit(HKEY_CURRENT_USER, PREINSTALLED_APPS_PATH, PREINSTALLED_NAME1, REG_DWORD, (BYTE*)& zero))
			success_messages << "<OEM Preinstalled Apps> disabled successfully\n";
		if (Regedit(HKEY_CURRENT_USER, PREINSTALLED_APPS_PATH, PREINSTALLED_NAME2, REG_DWORD, (BYTE*)& zero))
			success_messages << "<Preinstalled Apps> disabled successfully\n";
		if (Regedit(HKEY_CURRENT_USER, PREINSTALLED_APPS_PATH, PREINSTALLED_NAME3, REG_DWORD, (BYTE*)& zero))
			success_messages << "<Preinstalled Apps Ever> disabled successfully\n";
	}
	catch (const std::exception& e)
	{
		error_messages << e.what() << " --- this happened while disabling Silent Install\n";
	}
#pragma endregion

#pragma region Turn off suggested apps
	//turn off suggestions
	try
	{
		if (Regedit(HKEY_CURRENT_USER, SUGGESTIONS_PATH, SUGGESTIONS_NAME, REG_DWORD, (BYTE*)& zero))
			success_messages << "No longer showing suggestions\n";
	}
	catch (const std::exception& e)
	{
		error_messages << e.what() << " --- this happened while turning off suggestions\n";
	}
#pragma endregion

#pragma endregion

#pragma region Dont show recent folders
	//don't show recent folders
	try
	{
		if (Regedit(HKEY_CURRENT_USER, QUICKACCESS_PATH, QUICKACCESS_NAME, REG_DWORD, (BYTE*)&zero))
			success_messages << "No longer showing recent folders in quick access\n";
	}
	catch (const std::exception& e)
	{
		error_messages << e.what() << " --- this happened while disabling \"show recent folders\"\n";
	}
#pragma endregion

#pragma region Dont show frequently used folders
	//don't show frequently used folders
	try
	{
		if (Regedit(HKEY_CURRENT_USER, QUICKACCESS_PATH, FREQUENTS_NAME, REG_DWORD, (BYTE*)&zero))
			success_messages << "No longer showing frequent folders in quick access\n";
	}
	catch (const std::exception& e)
	{
		error_messages << e.what() << " --- this happened while disabling \"show frequent folders\"\n";
	}
#pragma endregion

	//#pragma region Disable Windows Store
	//	//disable Windows Store
	//	try
	//	{
	//		if (Regedit(HKEY_LOCAL_MACHINE, STORE_PATH, STORE_NAME, REG_DWORD, (BYTE*)&one))
	//			success_messages << "Windows Store disabled\n";
	//	}
	//	catch (const std::exception& e)
	//	{
	//		errors += e.what();
	//		errors += " --- this happened while disabling Windows Store\n";
	//	}
	//#pragma endregion

#pragma region Turn off User Account Control (UAC)
	//turn off User Account Control
	try
	{
		if (Regedit(HKEY_LOCAL_MACHINE, UAC_REGISTRY_PATH, UAC_NAME1, REG_DWORD, (BYTE*)&zero))
			if (Regedit(HKEY_LOCAL_MACHINE, UAC_REGISTRY_PATH, UAC_NAME2, REG_DWORD, (BYTE*)&zero))
				success_messages << "Changed User Account Control level\n";
	}
	catch (const std::exception& e)
	{
		error_messages << e.what() << " --- this happened while changing User Account Control";
	}
#pragma endregion

#pragma region Dont track recent documents
	//Store and display recently opened items in the Start menu and the taskbar
	try
	{
		if (Regedit(HKEY_CURRENT_USER, TRACKDOCS_PATH, TRACKDOCS_NAME, REG_DWORD, (BYTE*)&zero))
			success_messages << "No longer tracking recent documents\n";
	}
	catch (const std::exception& e)
	{
		error_messages << e.what() << " --- this happened while disabling document tracking\n";
	}
#pragma endregion

	cout << success_messages.rdbuf();

	if (error_messages.rdbuf()->in_avail() != 0) //fancy way of saying if str.isEmpty()
		cout << "\nThe following errors have occured:\n" << error_messages.rdbuf();
}

void displayHelp()
{
	cout << "\"settings\" will alter the (registry) default value of the following items. It will:\n"
		"\t\tDisable Cortana\n"
		"\t\tDisable ads (disables \"CloudContent\" in registry)\n"
		"\t\tDisable Windows Defender\n"
		"\t\tDisable Firewall\n"
		"\t\tDisable Windows Defender Tray Icon\n"
		"\t\tDisable Telemetry\n"
		"\t\tSet Windows Explorer to open to \"this PC\" instead of \"Quick Access\"\n"
		"\t\tDisable Group Taskbar (applications of the same type are no longer grouped)\n"
		"\t\tUnhide Folders\n"
		"\t\tUnhide Extensions\n"
		"\t\tAdd \"Open with notepad\" option to right click\n"
		"\t\tDisable recent folders\n"
		"\t\tDisable frequently used folders\n"
		//"\t\tDisable Windows Store (Xbox)\n"
		"\t\tDisable User Account Control\n"
		"\t\tChange date-time format from M / D / YYYY to DD - MMM - YY\n"
		"\t\tDisable OneDrive\n"
		"\t\tDisable Suggestions(apps)\n"
		"\t\tDisable Silent Install\n"
		"\t\tDisable TrackDocs\n\n\n"

		"\"uninstall\" will uninstall the following applications:\n"
		"\t 1)3D Builder\n"
		"\t 2)Get Office\n"
		"\t 3)Get Skype\n"
		"\t 4)Groove Music (just use VLC)\n"
		"\t 5)Windows Maps\n"
		"\t 6)Solitaire\n"
		"\t 7)Movies & TV\n"
		"\t 8)People\n"
		"\t 9)Voice Recorder\n"
		"\t10)Weather\n"
		"\t11)Bing News\n"
		"\t12)Mail\n"
		"\t13)Candy Crush\n"
		"\t14)SketchBook\n"
		"\t15)Feedback Hub\n"
		"\t16)3D Viewer\n";
}

void startUI()
{
	string input;
	vector<string> arguments;

	cout << "Welcome.\nThe commands to use this application are the following:\n"
		"exit\t\t-> Exists the application\n"
		"help\t\t-> Displays more information about other commands\n"
		"settings\t-> Changes the default registry settings. See \"help\" for more information\n"
		"uninstall\t-> Uninstalls some useless programs\n"
		"\n\Enter a command: ";

	bool ok = true;
	while (ok)
	{
		getline(cin, input);
		arguments = split(input, ' ');
		//cannot 'switch' on strings :/
		for (string s : arguments)
		{
			if (s == "exit")
				return;
			else if (s == "help")
				displayHelp();
			else if (s == "settings")
				Settings();
			else if (s == "uninstall")
				Uninstall();
		}
		system("pause");
	}
}
