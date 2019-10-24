#ifdef _WIN32
    #ifdef LOCALIZERDLL_EXPORTS
        #define DLL_IMPORT_EXPORT_LOCALIZERDLL  __declspec(dllexport)   // export DLL information
    #else
        #define DLL_IMPORT_EXPORT_LOCALIZERDLL  __declspec(dllimport)   // import DLL information
    #endif
#else
    #include <Qt/qglobal.h>
    #ifdef LOCALIZERDLL_EXPORTS
        #define DLL_IMPORT_EXPORT_LOCALIZERDLL Q_DECL_EXPORT // export shared library definitions
    #else
        #define DLL_IMPORT_EXPORT_LOCALIZERDLL Q_DECL_IMPORT // import shared library definitions
    #endif
#endif

#ifndef LOCALIZERHEADER_H
#define LOCALIZERHEADER_H

#include <string>
#include <vector>
#include <MathBib/Vector.h>
#include <MathBib/Matrix.h>

//class CVector;
//class CMatrix;
class CCommandHandling;



const int MAX_NUM_MARKERS = 12;
class DLL_IMPORT_EXPORT_LOCALIZERDLL CToolData
{
public:

	CToolData();
	~CToolData(){}
	//CToolData(const std::string &physicalPort);	///< Constructor with defining the PhysicalPort

	CToolData getRelativeTo(CToolData *toolData);	///< basically set a reference base
	bool isVisible();


	// Variables of the Object CToolData
	std::string toolName;				///< PartName of the tool
	std::string szPort;					///< m_pCommandHandling - m_dtHandleInformation[i].szPhysicalPort
	double	dQ0,dQx,dQy,dQz;			///< Quaternions
	CVector vT;						    ///< Tranlation-vector
	CMatrix mR;						    ///< RotationMatrix
	float	fRMSError;					///< Root Mean Square Error 
	bool	bOutOfVolume;				///< Tool out of volume
	bool	bVisible;					///< Tool is visible
	bool	bPartiallyOutOfVolume;		///< Tool partially out of volume
	bool	bInitialised;				///< Is the wired Tool initialized
	bool	bPivotMovementDetected;		///< Pivotmovement detected
	unsigned int iNumberOfVisibleMarkers; ///< Number of visible markers (single reflectors)
	unsigned int iTotalNumberOfMarkers; ///< total number of markers on the tool

	//CVector vMarkerPosition [MAX_NUM_MARKERS];
	void setSzPort(const std::string &sPort);	///< setMethod for szPort
	void setName(const std::string &sName);	///< setMethod for toolName
};

///< Localizer Exception 
class Loc_error : public std::logic_error
{
public :
	Loc_error (const std::string& what_arg);
};


class DLL_IMPORT_EXPORT_LOCALIZERDLL CLocalizer
{
public:
	// creates CommandHandling-Object
	CLocalizer(void);	///< Standard Constructor creates an object of CommandHandling
	virtual ~CLocalizer(void);
	std::string sError;	///< String to store ErrorMessages in

	///! LoadIni > Open > nActivateAllPorts 
	virtual int open(const std::string &programPath, const std::string &iniFileName);	///< Opens the Localizer by loading the IniFile, opening the Comport and activating the wired Tools

	///! nGetBXTransforms > getToolData is used in Trackingthread
	virtual bool getToolData();	///< only get transforms without writing the data 
	virtual bool getToolData(CToolData &oneToolData, bool updateFlag=true);	///< Update Tooldata for one single Tool

	///< nGetHandleInformation ... if the tool that we created before is found in one of the HandleInformations
	///< set the variables of the CToolData with the updated information
	virtual bool getToolData(const std::vector<CToolData*> &m_aToolData,bool updateFlag=true);	///< Update the ToolData for a vector of ToolData
	
	//not tested yet
	int getFreeMarkerPosition(std::vector<CVector> &m_aMarkerPositions);
	//not done yet
	bool loadROM(const std::string &port);
	///< sends the command "TSTART" to the camera in CCommandHandling
	virtual bool startTracking();
	///< sends the command "TSTOP" to the camera in CCommandHandling
	virtual bool stopTracking();
	int getVolume();
	int setVolume();
	void setGetVisibleMarkersForTools(const bool &bValue);
	///< returns the HandleNumber of the tool defined by szPort
	int checkHandle(const std::string &port);
	///< returns the Partname of the tool found on the given HandleNumber
	std::string checkPartName(const int &x);
	void GetErrorText(const char *iCodeError, std::string *pszErrorMsg);		///< This method gets the error messages
	std::string GetErrorText(const char* iCodeError); ///< This method returns the error message or null
	///< returns m_bSystemInitialized
	bool isInitialized();
	bool isTracking();

	bool setFiringRate(int rate);
/////////////////////OLD INTERFACECLASS////////////////////
protected:
	// Public Methods. These methods correspond to level 0 of the interface offered by this DLL.
	
	int LoadIni(const std::string &szProgramPath, const std::string &szLocalizerIniFile);	///< This method loads variables from the ini-file in which several ROM-Files are assigned to different ports
	int Open(void);						///< This method stablishes communication between localizer and computer
	void SetMode(const int &nMode );	///< This method manages the mode of the system

// Public variables
//	CRITICAL_SECTION m_CriticalSection;	///< Controls access to shared resources
	bool m_bSystemInitialized;			///< Is the system initialized
	bool m_bPortsActivated;				///< Are ports activated 
	bool m_bGetVisibleMarkersForTools;	///< Should number of visible markers for tools be returned with tooldata (default: false)
	
	bool m_bIsTracking;
private:
	CCommandHandling *m_pCommandHandling;
	unsigned long m_ulLastFrameNumber;

};

#endif

