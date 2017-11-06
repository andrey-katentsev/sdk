/* Designed and programmed by Hyperlink, 2008. */
/* Copyright by Hyperlink */
/* Contacts: */
/* e-mail: hyperlink@inbox.ru */
/* UIN: 282757076 */

/* Wave PCM class header file */

#ifndef HS_PCMWAVEFORMAT_CLASS
#define HS_PCMWAVEFORMAT_CLASS

#define DIRECTX

#include <windows.h>
#include <dsound.h>

#define PCMWAVEFORMAT_OFFSET 20
#define WAVE_HEADER_SIZE 44

#define WAVE_PCM_8BIT_SILENCE 128
#define WAVE_PCM_16BIT_SILENCE 0

#define WAVE_PCM_SILENCE(BPS) ((BPS==8)?WAVE_PCM_8BIT_SILENCE:WAVE_PCM_16BIT_SILENCE)

typedef struct tagRIFFHeader
{
	BYTE bRiffID[4];
	DWORD dwRiffSize;
	BYTE bRiffFormat[4];
} RIFFHEADER;
typedef RIFFHEADER *PRIFFHEADER;
typedef RIFFHEADER NEAR *NPRIFFHEADER;
typedef RIFFHEADER FAR *LPRIFFHEADER;

typedef struct tagPCMWaveFormatDescriptor
{
	BYTE bFmtId[4];
	DWORD dwFmtSize;
	PCMWAVEFORMAT sFmtFormat;
} PCMWAVEFORMATDESCRIPTOR;
typedef PCMWAVEFORMATDESCRIPTOR *PPCMWAVEFORMATDESCRIPTOR;
typedef PCMWAVEFORMATDESCRIPTOR NEAR *NPPCMWAVEFORMATDESCRIPTOR;
typedef PCMWAVEFORMATDESCRIPTOR FAR *LPPCMWAVEFORMATDESCRIPTOR;

typedef struct tagFileAdditionalControlTag
{
	BYTE bFactID[4];
	DWORD dwReserved1;
	DWORD dwReserved2;
} FILEADDITIONALCONTROLTAG;
typedef FILEADDITIONALCONTROLTAG *PFILEADDITIONALCONTROLTAG;

typedef struct tagDataDescriptor
{
	BYTE bDataId[4];
	DWORD dwDataSize;
	LPVOID lpData;
} DATADESCRIPTOR;
typedef DATADESCRIPTOR *PDATADESCRIPTOR;
typedef DATADESCRIPTOR NEAR *NPDATADESCRIPTOR;
typedef DATADESCRIPTOR FAR *LPDATADESCRIPTOR;

/* PCM *.wav file structure */
// 12 bytes: Riff header
// 24 bytes: Riff format description
// 12 bytes: Unknown block (FACT) (may miss)
// 8 bytes: Data description block
// ? bytes: Wave data

typedef class tagHSPCMWave
{
private:
	/*DWORD dwBytesLeft;
	DWORD dwBytesRead;*/
protected:
	BYTE *pbPCMWaveData;             // PCM Wave data pointer
	LPPCMWAVEFORMAT lpPCMWaveHeader; // PCM Wave header pointer
	DWORD dwCurrentPosition ;        // Current read position
	DWORD dwWaveSize;                // Wave data size
public:
	tagHSPCMWave();
	~tagHSPCMWave();

	VOID Close(VOID);
	BOOL Open(LPCSTR lpFileName);
	DWORD Read(BYTE *pbWaveData,DWORD nDataSize);
	VOID Reset(VOID);

	DWORD GetWaveSize(VOID);
	BOOL GetWaveHeader(LPPCMWAVEFORMAT lpPCMWaveHeader);
} HSPCMWAVE;

typedef HSPCMWAVE *PHSPCMWAVE;
typedef HSPCMWAVE FAR *LPHSPCMWAVE;
typedef HSPCMWAVE NEAR *NPHSPCMWAVE;

#endif