#pragma once
#include <Windows.h>

#define CORTANA_NAME	"AllowCortana"
#define ADS_NAME		"DisableWindowsConsumerFeatures"
#define ADS_INFO_NAME	"Enabled"
#define SILENT_NAME		"SilentInstalledAppsEnabled"
#define DELIVERY_NAME	"ContentDeliveryAllowed"
#define DEFENDER_NAME	"DisableAntiSpyware"
#define DEFENDER_ICON	"SecurityHealth"
#define TELEMETRY_NAME	"AllowTelemetry"
#define EXPLORER_THISPC	"LaunchTo"
#define TASKBAR_NOGROUP	"TaskbarGlomLevel"
#define HIDE_FOLDERS	"Hidden"
#define HIDE_EXTENSIONS	"HideFileExt"
#define TASKVIEW_BUTTON	"ShowTaskViewButton"
#define NOTEPAD_EXEC	"notepad.exe %1\0"
#define QUICKACCESS_NAME "ShowRecent"
#define FREQUENTS_NAME	"ShowFrequent"
#define DATETIME_NAME1 "iDate"
#define DATETIME_NAME2 "sDate"
#define DATETIME_NAME3 "sShortDate"
#define SERVICE_TELEMETRY1	"dmwappushservice"
#define STORE_NAME			"RemoveWindowsStore"
#define UAC_NAME1			"ConsentPromptBehaviorAdmin"
#define UAC_NAME2			"PromptOnSecureDesktop"
#define ONEDRIVE_NAME		"OneDrive"
#define SUGGESTIONS_NAME	"SystemPaneSuggestionsEnabled"
#define SOFTLANDING_NAME	"SoftLandingEnabled"
#define TRACKDOCS_NAME		"Start_TrackDocs"
#define TASKBARSPEED_NAME	"ExtendedUIHoverTime"
#define PREINSTALLED_NAME1	"OemPreInstalledAppsEnabled"
#define PREINSTALLED_NAME2	"PreInstalledAppsEnabled"
#define PREINSTALLED_NAME3	"PreInstalledAppsEverEnabled"
#define FIREWALL_NAME		"EnableFirewall"
#define SEARCH_BAR			"SearchboxTaskbarMode"

#define SEARCH_BAR_PATH			"Software\\Microsoft\\Windows\\CurrentVersion\\Search"
#define ONEDRIVE_REGISTRY_PATH	"Software\\Microsoft\\Windows\\CurrentVersion\\Run"
#define DEFENDER_ICON_PATH		"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"
#define QUICKACCESS_PATH		"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer"
#define TRACKDOCS_PATH			"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced"
#define EXPLORER_REGISTER_PATH	"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced"
#define UAC_REGISTRY_PATH		"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"
#define SUGGESTIONS_PATH		"Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager"
#define SILENT_INSTALL_PATH		"Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager"
#define SOFTLANDING_PATH		"Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager"
#define PREINSTALLED_APPS_PATH	"Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager"
#define ADVERTISING_INFO_PATH	"Software\\Microsoft\\Windows\\CurrentVersion\\AdvertisingInfo"
#define DEFENDER_REGISTER_PATH	"SOFTWARE\\Policies\\Microsoft\\Windows Defender"
#define ADS_REGISTER_PATH		"SOFTWARE\\Policies\\Microsoft\\Windows\\CloudContent"
#define CORTANA_REGISTER_PATH	"SOFTWARE\\Policies\\Microsoft\\Windows\\Windows Search"
#define TELEMETRY_REGISTER_PATH	"SOFTWARE\\Policies\\Microsoft\\Windows\\DataCollection"
#define DATETIME_PATH			"Control Panel\\International"
#define STORE_PATH				"SOFTWARE\\Policies\\Microsoft\\WindowsStore"
#define FIREWALL_PATH1			"SOFTWARE\\Policies\\Microsoft\\WindowsFirewall\\DomainProfile"
#define FIREWALL_PATH2			"SOFTWARE\\Policies\\Microsoft\\WindowsFirewall\\StandardProfile"

#define NOTEPAD_ADDON "*\\shell\\Open with Notepad\\command"

#define BUILDER3D	"start powershell.exe \"Get-AppxPackage *3dbuilder* | Remove-AppxPackage\""
#define GETOFFICE	"start powershell.exe \"Get-AppxPackage *officehub* | Remove-AppxPackage\""
#define GETSKYPE	"start powershell.exe \"Get-AppxPackage *skypeapp* | Remove-AppxPackage\""
#define GROOVEMUSIC	"start powershell.exe \"Get-AppxPackage *zunemusic* | Remove-AppxPackage\""
#define	MAPS_WIN	"start powershell.exe \"Get-AppxPackage *windowsmaps* | Remove-AppxPackage\""
#define	SOLITAIRE	"start powershell.exe \"Get-AppxPackage *solitairecollection* | Remove-AppxPackage\""
#define	VIDEO		"start powershell.exe \"Get-AppxPackage *zunevideo* | Remove-AppxPackage\""
#define	PEOPLE		"start powershell.exe \"Get-AppxPackage *people* | Remove-AppxPackage\""
#define	STORE		"start powershell.exe \"Get-AppxPackage *windowsstore* | Remove-AppxPackage\""
#define RECORDER	"start powershell.exe \"Get-AppxPackage *soundrecorder* | Remove-AppxPackage\""
#define WEATHER		"start powershell.exe \"Get-AppxPackage *bingweather* | Remove-AppxPackage\""
#define XBOX_APP	"start powershell.exe \"Get-AppxPackage *xboxapp* | Remove-AppxPackage\""
#define NEWS_APP	"start powershell.exe \"Get-AppxPackage *bingnews* | Remove-AppxPackage\""
#define MAIL_APP	"start powershell.exe \"Get-AppxPackage *windowscommunicationsapps* | Remove-AppxPackage\""
#define CANDY_CRUSH	"start powershell.exe \"Get-AppxPackage *CandyCrushSodaSaga* | Remove-AppxPackage\""
#define SKETCHBOOK	"start powershell.exe \"Get-AppxPackage *AutodeskSketchBook* | Remove-AppxPackage\""
#define FEEDBACKHUB	"start powershell.exe \"Get-AppxPackage *WindowsFeedbackHub* | Remove-AppxPackage\""
#define VIEWER3D	"start powershell.exe \"Get-AppxPackage *3DViewer* | Remove-AppxPackage\""

PHKEY Register_Create(HKEY machine, LPCTSTR key);
PHKEY Register_Open(HKEY machine, LPCTSTR key);
DWORD Register_GetDWORD(HKEY machine, LPCTSTR valName);
char* Register_GetSTR(HKEY machine, LPCTSTR valName, LPCTSTR keyPath = NULL);
void  Register_SetValue(HKEY machine, LPCTSTR valName, DWORD type, LPCBYTE value);
bool  Register_DelValue(HKEY machine, LPCTSTR valName, LPCTSTR keyPath = NULL);

bool Regedit(HKEY machine, LPCTSTR keyPath, LPCTSTR valName, DWORD type, LPCBYTE value);
void ServiceEdit(LPCSTR svcName, DWORD startTime);