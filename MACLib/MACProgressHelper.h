#pragma once

namespace APE
{

#define KILL_FLAG_CONTINUE          0
#define KILL_FLAG_PAUSE             -1
#define KILL_FLAG_STOP              1

class IAPEProgressCallback;

class CMACProgressHelper  
{
public:
    
    CMACProgressHelper(int nTotalSteps, IAPEProgressCallback * pProgressCallback);
    virtual ~CMACProgressHelper();

    void UpdateProgress(int nCurrentStep = -1, BOOL bForceUpdate = FALSE);
    void UpdateProgressComplete() { UpdateProgress(m_nTotalSteps, TRUE); }

    int ProcessKillFlag(BOOL bSleep = TRUE);
    
private:
    IAPEProgressCallback * m_pProgressCallback;
    int m_nTotalSteps;
    int m_nCurrentStep;
    int m_nLastCallbackFiredPercentageDone;
};

}
