#include <advanlys.h>
#include <utility.h>
#include <formatio.h>
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "APD_proiect.h"

#define SAMPLE_RATE 0
#define NPOINTS 1
#define PI 3.14159265358979323846

static int mainPanel;
static int freqPanel;

double fstop=1200;
double fpass=1500;

char fileName[255];
int bitmapID=0;
int waveInfo[2];//unde waveInfo[0]-sampleRate, waveinfo[1]-nr de puncte
double sampleRate=0.0;
int npoints=0;
double waveData[1000000];
double *envelopeData=0;
size_t *hist=0;
double *axis=0;
double*derivata=0;
int zeros=0;
double *filt=0;
double *esantion=0;
double min,max,dispersie,medie,mediana;
int minInd,maxInd;
double skew,kurtosis;
size_t count=0;
double *peakLocation=0;
double *peakAmplitude=0;
double *peakSD=0;
double *envelopeDataNeg=0;
unsigned int start=0;
double *fereastra = 0;

//functii
int ComputePowerSpectrum(double input[],unsigned int noElements,unsigned int start,double sampleRate, double convertedSpectrum[], double *freqInterval, double *powerPeak,double *freqPeak);
void Filtru(double input[],int start,int N);
void Fereastra(double input[],int start,int N);
void Blackman(double input[],int noElements,double output[],int start);
void BlackmanHarris(double input[],int noElements,double output[],int start);


void Derivata(){
	derivata=(double*)calloc(npoints,sizeof(double));
	for(int i=1;i<npoints;i++)
		derivata[i-1]=waveData[i]-waveData[i-1];
}

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((mainPanel = LoadPanel (0, "APD_proiect.uir", MAIN_PANEL)) < 0)
		return -1;
	if ((freqPanel = LoadPanel (0, "APD_proiect.uir", FREQ_PANEL)) < 0)
		return -1;
	DisplayPanel (mainPanel);
	
	RunUserInterface ();
	DiscardPanel (mainPanel);
	return 0;
}

int CVICALLBACK OnMainPanel (int panel, int event, void *callbackData,
							 int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			//free(waveData);
			free(esantion);
			free(envelopeData);
			free(hist);
			free(axis);
			free(filt);
			free(fereastra);
			QuitUserInterface(0);
			break;
	}
	return 0;
}

int  CVICALLBACK OnFreqPanel(int panel, int event, void *callbackData, int eventData1, int eventData2){
	if(event==EVENT_CLOSE)
	{QuitUserInterface(0);
	free(esantion);
			free(envelopeData);
			free(hist);
			free(axis);
			free(filt);
			free(fereastra);}
	
	return 0;
}

int CVICALLBACK OnAplicaButton (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			int val;
			int med;
			double alpha=0.0;
			filt=(double*)calloc(npoints,sizeof(double));
			filt[0]=waveData[0];
			GetCtrlVal(panel,MAIN_PANEL_IDC_FILTRU,&val);
			DeleteGraphPlot(panel,MAIN_PANEL_IDC_GRAPH,-1,VAL_IMMEDIATE_DRAW);
			if(val==1){
				GetCtrlVal(panel,MAIN_PANEL_IDC_ALPHA,&alpha);
				for(int i=1;i<npoints;i++){
					filt[i]=(1-alpha)*filt[i-1]+alpha*waveData[i];
				}
				
			}
			else{
				GetCtrlVal(panel,MAIN_PANEL_IDC_MEDIERE,&med);
				double sum=waveData[0];
				for(int i=1;i<med;i++){
					sum+=waveData[i];
					filt[i]=sum/(i+1);
				}
				for(int i=med;i<npoints;i++){
					sum+=waveData[i];
					sum-=waveData[i-med];
					filt[i]=sum/med;
				}
			}
				PlotY(panel, MAIN_PANEL_IDC_GRAPH, filt, npoints, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS, VAL_RED);
			break;
	}
	return 0;
}


int CVICALLBACK OnNextButton (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			int start,stop;
			GetCtrlVal(panel,MAIN_PANEL_IDC_START,&start);
			GetCtrlVal(panel,MAIN_PANEL_IDC_STOP,&stop);
			start++;
			stop++;
			if(start<0){
					start=0;
					stop=1;					
			}
			else
				if(stop>5)
			{
				stop=5;
				start=4;
			}
			SetCtrlVal(panel,MAIN_PANEL_IDC_START,start);
			SetCtrlVal(panel,MAIN_PANEL_IDC_STOP,stop);
			SetAxisScalingMode(panel,MAIN_PANEL_IDC_GRAPH_RAW_DATA,VAL_BOTTOM_XAXIS,VAL_MANUAL,start*sampleRate,stop*sampleRate);
			SetAxisScalingMode(panel,MAIN_PANEL_IDC_GRAPH,VAL_BOTTOM_XAXIS,VAL_MANUAL,start*sampleRate,stop*sampleRate);
			
			sprintf(fileName, "D:\\APD\\APD_Proiect\\APD_Proiect\\Grafice\\g_%0d_%0d.jpg",start,stop);//generare nume fisier
			GetCtrlDisplayBitmap(panel, MAIN_PANEL_IDC_GRAPH_RAW_DATA, 1, &bitmapID); 
			SaveBitmapToJPEGFile(bitmapID, fileName, JPEG_PROGRESSIVE, 100); 
			break;
	}
	return 0;
}


int CVICALLBACK OnPrevButton (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			int start,stop;
			GetCtrlVal(panel,MAIN_PANEL_IDC_START,&start);
			GetCtrlVal(panel,MAIN_PANEL_IDC_STOP,&stop);
			start--;
			stop--;
			if(start<0){
					start=0;
					stop=1;					
			}
			else
				if(stop>5)
			{
				stop=5;
				start=4;
			}
			SetCtrlVal(panel,MAIN_PANEL_IDC_START,start);
			SetCtrlVal(panel,MAIN_PANEL_IDC_STOP,stop);
			SetAxisScalingMode(panel,MAIN_PANEL_IDC_GRAPH_RAW_DATA,VAL_BOTTOM_XAXIS,VAL_MANUAL,start*sampleRate,stop*sampleRate);
			SetAxisScalingMode(panel,MAIN_PANEL_IDC_GRAPH,VAL_BOTTOM_XAXIS,VAL_MANUAL,start*sampleRate,stop*sampleRate);
			
			sprintf(fileName, "D:\\APD\\APD_Proiect\\APD_Proiect\\Grafice\\g_%0d_%0d.jpg",start,stop);//generare nume fisier
			GetCtrlDisplayBitmap(panel, MAIN_PANEL_IDC_GRAPH_RAW_DATA, 1, &bitmapID); 
			SaveBitmapToJPEGFile(bitmapID, fileName, JPEG_PROGRESSIVE, 100); 
			break;
	}
	return 0;
}


int CVICALLBACK OnExit (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			QuitUserInterface(0);
			break;
	}
	return 0;
}



int CVICALLBACK OnLoadButton (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			//executa script python pentru conversia unui fisierului .wav in .txt
			LaunchExecutable("python proiect_apd.py");
			
			//astept sa fie generate cele doua fisiere (modificati timpul daca este necesar
			Delay(4);
			//incarc informatiile privind rata de esantionare si numarul de valori
			FileToArray("wafeInfo.txt", waveInfo, VAL_INTEGER, 2, 1, VAL_DATA_MULTIPLEXED, VAL_GROUPS_AS_COLUMNS, VAL_ASCII);
			sampleRate = waveInfo[SAMPLE_RATE];
			npoints = waveInfo[NPOINTS];		
			envelopeData=(double*)calloc(npoints,sizeof(double)); //anvelopa
			envelopeDataNeg=(double*)calloc(npoints,sizeof(double));
			FileToArray("envelope.txt", envelopeData, VAL_DOUBLE, npoints, 2, VAL_DATA_MULTIPLEXED, VAL_GROUPS_AS_COLUMNS, VAL_ASCII);
			PlotY(panel, MAIN_PANEL_IDC_GRAPH_RAW_DATA, envelopeData, npoints, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS, VAL_BLACK);
			
			FileToArray("canal1.txt", waveData, VAL_DOUBLE, npoints, 2, VAL_DATA_MULTIPLEXED, VAL_GROUPS_AS_COLUMNS, VAL_ASCII);
			
			//afisare pe grapf
			PlotY(panel, MAIN_PANEL_IDC_GRAPH_RAW_DATA, waveData, npoints, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS, VAL_RED);
			
			MaxMin1D(waveData,npoints,&max,&maxInd,&min,&minInd);
			//Mean(waveData,npoints,&medie); // se  calculeaza o data cu dispersia
			Median(waveData,npoints,&mediana);
			Variance(waveData,npoints,&medie,&dispersie);
			SetCtrlVal(panel,MAIN_PANEL_IDC_DISPERSIE,dispersie);
			SetCtrlVal(panel,MAIN_PANEL_IDC_MEDIE,medie);
			SetCtrlVal(panel,MAIN_PANEL_IDC_VMAX,max);
			SetCtrlVal(panel,MAIN_PANEL_IDC_VMAX_INDEX,maxInd);
			SetCtrlVal(panel,MAIN_PANEL_IDC_VMIN,min);
			SetCtrlVal(panel,MAIN_PANEL_IDC_VMIN_INDEX,minInd);
			SetCtrlVal(panel,MAIN_PANEL_IDC_MEDIANA,mediana);
			esantion=(double*)calloc(256,sizeof(double));
			for(int i=0;i<256;i++)
				esantion[i]=waveData[i];
			
			Moment(esantion,256,3,&skew);
			Moment(esantion,256,4,&kurtosis);
			SetCtrlVal(panel,MAIN_PANEL_IDC_KURTOSIS,kurtosis);
			SetCtrlVal(panel,MAIN_PANEL_IDC_SKEWNESS,skew);
			
			hist=(size_t*)calloc(20,sizeof(size_t));
			axis=(double*)calloc(20,sizeof(double));
			Histogram(waveData,npoints,min,max,hist,axis,20);
			PlotXY(panel,MAIN_PANEL_IDC_HISTOGRAM,axis,hist,20,VAL_DOUBLE,VAL_SIZE_T,VAL_VERTICAL_BAR,VAL_SMALL_SOLID_SQUARE,VAL_SOLID,VAL_CONNECTED_POINTS,VAL_MAGENTA);
			for(int i=0;i<npoints-1;i++)
			{	if(waveData[i]==0)
					zeros++;
				if(waveData[i]>0&&waveData[i+1]<0)
					zeros++;
				if(waveData[i]<0&&waveData[i+1]>0)
					zeros++;
				
			}
			SetCtrlVal(panel,MAIN_PANEL_IDC_ZEROS,zeros);
			
			fereastra=(double *)calloc(npoints,sizeof(double));//fac o copie
			for(int i=0;i<npoints;i++)
				fereastra[i]=waveData[i];
			
			break;
	}
	return 0;
}


int CVICALLBACK OnDerivata (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			Derivata();
			PlotY(panel,MAIN_PANEL_IDC_GRAPH_RAW_DATA,derivata,npoints,VAL_DOUBLE,VAL_THIN_LINE,VAL_EMPTY_CIRCLE,VAL_SOLID,VAL_CONNECTED_POINTS,VAL_BLUE);
			break;
	}
	return 0;
}
int  CVICALLBACK OnBinarySwitch(int panel, int control, int event, void *callbackData, int eventData1, int eventData2){
	switch(event){
	
		case EVENT_COMMIT:
		if(panel==mainPanel){
			SetCtrlVal(freqPanel,FREQ_PANEL_BINARYSWITCH,1);
			DisplayPanel(freqPanel);
			HidePanel(panel);
			SetCtrlAttribute(freqPanel,FREQ_PANEL_TIMER,ATTR_ENABLED, 0);
		}
		else
		{
			SetCtrlVal(mainPanel,MAIN_PANEL_BINARYSWITCH,0);
			DisplayPanel(mainPanel);
			HidePanel(panel);
		}
		
		break;
	}
	return 0;
}
int  CVICALLBACK OnExitFreq(int panel, int control, int event, void *callbackData, int eventData1, int eventData2){

	switch (event)
	{
		case EVENT_COMMIT:
			QuitUserInterface(0);
			break;
	}
	return 0;
}
int  CVICALLBACK OnTimer(int panel, int control, int event, void *callbackData, int eventData1, int eventData2){

	switch(event){
		case EVENT_TIMER_TICK:
			
			int N;
			
			GetCtrlVal(freqPanel,FREQ_PANEL_NUMERIC,&N);//Dimensiunea ferestrei pentru care aplicam FFT;
			
		
			if(panel==freqPanel){
				
			
			if(start+N<=npoints){
			
				//afisez esantionat semnalul initial fara ferestruire sau filtru
				//SetAxisRange(freqPanel,FREQ_PANEL_GRAPH_FREQ_SIGNAL,VAL_MANUAL,start,start+N,VAL_AUTOSCALE,0,0);	
				DeleteGraphPlot(freqPanel,FREQ_PANEL_GRAPH_FREQ_SIGNAL,-1,VAL_IMMEDIATE_DRAW);
				PlotY(freqPanel,FREQ_PANEL_GRAPH_FREQ_SIGNAL,waveData+start,N,VAL_DOUBLE,VAL_THIN_LINE,VAL_EMPTY_SQUARE,VAL_SOLID,VAL_CONNECTED_POINTS,VAL_RED);	
			
				Fereastra(fereastra+start,start,N);//aplic pe semnalul initial ferestruirea si calculez spectru
				
				sprintf(fileName,"D:\\APD\\APD_Proiect\\APD_Proiect\\Grafice_Etapa2\\fereastra\\gwindow_%0d_%0d.jpg",start,start+N);//generare nume fisier
				GetCtrlDisplayBitmap(freqPanel, FREQ_PANEL_GRAPH_FREQ_WINDOW, 1, &bitmapID); 
				SaveBitmapToJPEGFile(bitmapID, fileName, JPEG_PROGRESSIVE, 100); 
				
				sprintf(fileName,"D:\\APD\\APD_Proiect\\APD_Proiect\\Grafice_Etapa2\\spectru_fereastra\\gswindow_%0d_%0d.jpg",start,start+N);//generare nume fisier
				GetCtrlDisplayBitmap(freqPanel, FREQ_PANEL_GRAPH_SPECTRU, 1, &bitmapID); 
				SaveBitmapToJPEGFile(bitmapID, fileName, JPEG_PROGRESSIVE, 100); 
				
				
				Filtru(waveData+start,start,N);//aplic filtru, dupa care fereastra si calculez spectru
				
				sprintf(fileName,"D:\\APD\\APD_Proiect\\APD_Proiect\\Grafice_Etapa2\\filtru_fereastra\\gfiltru_%0d_%0d.jpg",start,start+N);//generare nume fisier
				GetCtrlDisplayBitmap(freqPanel, FREQ_PANEL_GRAPH_FREQ_FILTER, 1, &bitmapID); 
				SaveBitmapToJPEGFile(bitmapID, fileName, JPEG_PROGRESSIVE, 100); 
				
				sprintf(fileName,"D:\\APD\\APD_Proiect\\APD_Proiect\\Grafice_Etapa2\\spectru_filtru_fereastra\\gsfiltru_%0d_%0d.jpg",start,start+N);//generare nume fisier
				GetCtrlDisplayBitmap(freqPanel, FREQ_PANEL_GRAPH_SPECTRU_2, 1, &bitmapID); 
				SaveBitmapToJPEGFile(bitmapID, fileName, JPEG_PROGRESSIVE, 100); 
			
				
				start=start+N;//actualizez valoarea de start
			
				}
			}
			else{
				start=0;
				SetCtrlAttribute(freqPanel,FREQ_PANEL_TIMER,ATTR_ENABLED, 0);
			}
				
		break;	
	}
	return 0;
}

int CVICALLBACK OnTimerGo (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute(freqPanel,FREQ_PANEL_TIMER,ATTR_ENABLED,1);
			break;
	}
	return 0;
}
int ComputePowerSpectrum(double input[],unsigned int noElements,unsigned int start,double sampleRate, double convertedSpectrum[], double *freqInterval, double *powerPeak,double *freqPeak){
			//voltage signal -descrierea semnalului achizitionat
			char unit[32]="V";
			
			//spectrul de putere cu un numar de valori egal cu jumatate din dimensiunea bufferuli de intrare
			double *autoSpectrum=0;
			autoSpectrum=(double*)calloc(noElements/2,sizeof(double));
			WindowConst winConst;
			//aplatizare forma semnal la capetele intervalului
			ScaledWindow(input,noElements,RECTANGLE_,&winConst); 
	
			//calculeaza puterea si frecventa corespunzatoare varfului din spectrul semnalului
			AutoPowerSpectrum(input,noElements,1.0/sampleRate,convertedSpectrum,freqInterval);
			
			//functia converteste  spectrul de intrare (care este puterea,aplitudinea sau amplificarea) in formate alternative (linear,logaritmic,dB) ce permit o reprezentare grafica mai buna
			PowerFrequencyEstimate(convertedSpectrum,noElements/2,-1.0,winConst,*freqInterval,7,freqPeak,powerPeak);
			
			SpectrumUnitConversion(convertedSpectrum,noElements/2,SPECTRUM_POWER,SCALING_MODE_LINEAR,DISPLAY_UNIT_VRMS,*freqInterval,winConst,convertedSpectrum,unit);
			
			
	
	return 0;
}

void Filtru(double input[],int start,int N){
						
			double *coef =0;
			double * output=0;
			double delta=0.0;
			
			int filtru=0;
			GetCtrlVal(freqPanel,FREQ_PANEL_FILTER_TYPE,&filtru);
			
			int window=0;
			GetCtrlVal(freqPanel,FREQ_PANEL_WINDOW_TYPE,&window);
			
			int noCoef;
			int freqCut;
			GetCtrlVal(freqPanel,FREQ_PANEL_COEFICIENTI,&noCoef);
			GetCtrlVal(freqPanel,FREQ_PANEL_FCUT,&freqCut);
			
			
			coef=(double *) calloc(noCoef,sizeof(double));
			
			double fpowerPeak=0.0; //frecventa estimata pentru spectrul de putere (maxim) din vectorul autoSpectrum
			double wfreqPeak=0.0;// pasul in domeniul frecventei
			double wdf=0.0;
		
			double *fconvertedSpectrum=0;//vector ce contine spectrul semnalului convertit la volti
			fconvertedSpectrum=(double*)calloc(N,sizeof(double));
			
			
			
			if(filtru==0) //aplic filtru 0--Ripple trece jos 1--pentru eliptic trece-jos 
			{
				output=(double *) calloc(N+noCoef-1,sizeof(double));
				EquiRpl_LPF(sampleRate,fstop,fpass, noCoef,coef,&delta);
				Convolve(coef,noCoef,input,N,output); 
				
			}
			else{
				output=(double *)calloc(N,sizeof(double));
				if(freqCut>0.5*sampleRate)
					freqCut=0.5*sampleRate-100;
				Elp_LPF(input,N,sampleRate,freqCut,0.1,40,5,output);
			}
			
			if(window==0) //aplic ferestruirea pe semnalul filtrat 0 -- fereastra Blackman; 1 -- fereastra Blackman-Harris 
			{	
				BkmanWin(output,N);
				
			}
			else{
				BlkHarrisWin(output,N);
			}
			
			
			DeleteGraphPlot(freqPanel,FREQ_PANEL_GRAPH_FREQ_FILTER,-1,VAL_IMMEDIATE_DRAW);
			PlotY(freqPanel,FREQ_PANEL_GRAPH_FREQ_FILTER,output,N,VAL_DOUBLE,VAL_THIN_LINE,VAL_SOLID_SQUARE,VAL_SOLID,VAL_CONNECTED_POINTS,VAL_RED);
			
			//spectru pentru semnalul filtrat
			ComputePowerSpectrum(output,N,start,sampleRate,fconvertedSpectrum,&wdf,&fpowerPeak,&wfreqPeak);
			SetCtrlVal(freqPanel,FREQ_PANEL_IDC_POWER_PEAK_2,fpowerPeak);
			SetCtrlVal(freqPanel,FREQ_PANEL_IDC_FREQ_PEAK_2,wfreqPeak);
			DeleteGraphPlot(freqPanel,FREQ_PANEL_GRAPH_SPECTRU_2,-1,VAL_IMMEDIATE_DRAW);
			PlotWaveform(freqPanel,FREQ_PANEL_GRAPH_SPECTRU_2,fconvertedSpectrum,N/2,VAL_DOUBLE,1.0,0.0,0.0,wdf,VAL_THIN_LINE,VAL_EMPTY_SQUARE,VAL_SOLID,VAL_CONNECTED_POINTS,VAL_DK_GREEN);
	
}

void Fereastra(double input[],int start,int N){
			//int N;
			//GetCtrlVal(freqPanel,FREQ_PANEL_NUMERIC,&N);
			
			double powerPeak=0.0; //frecventa estimata pentru spectrul de putere (maxim) din vectorul autoSpectrum
			double freqPeak=0.0;// pasul in domeniul frecventei
			double df=0.0;
			double *convertedSpectrum=0;//vector ce contine spectrul semnalului convertit la volti
			convertedSpectrum=(double*)calloc(N,sizeof(double));
			
			int window=0;
			GetCtrlVal(freqPanel,FREQ_PANEL_WINDOW_TYPE,&window);
					
			
			if(window==0) //aplic ferestruirea pe semnalul filtrat 0 -- fereastra Blackman; 1 -- fereastra Blackman-Harris 
			{	
				//BkmanWin(fereastra,N);
				Blackman(waveData,N,fereastra,start);
			}
			else{
				//BlkHarrisWin(fereastra,N);
				BlackmanHarris(waveData,N,fereastra,start);
			}
			
			DeleteGraphPlot(freqPanel,FREQ_PANEL_GRAPH_FREQ_WINDOW,-1,VAL_IMMEDIATE_DRAW);
			PlotY(freqPanel,FREQ_PANEL_GRAPH_FREQ_WINDOW,fereastra,N,VAL_DOUBLE,VAL_THIN_LINE,VAL_SOLID_SQUARE,VAL_SOLID,VAL_CONNECTED_POINTS,VAL_RED);
			
			ComputePowerSpectrum(fereastra,N,start,sampleRate,convertedSpectrum,&df,&powerPeak,&freqPeak); //calculez spectrul
			SetCtrlVal(freqPanel,FREQ_PANEL_IDC_POWER_PEAK,powerPeak);
			SetCtrlVal(freqPanel,FREQ_PANEL_IDC_FREQ_PEAK,freqPeak);
			DeleteGraphPlot(freqPanel,FREQ_PANEL_GRAPH_SPECTRU,-1,VAL_IMMEDIATE_DRAW);
			PlotWaveform(freqPanel,FREQ_PANEL_GRAPH_SPECTRU,convertedSpectrum,N/2,VAL_DOUBLE,1.0,0.0,0.0,df,VAL_THIN_LINE,VAL_EMPTY_SQUARE,VAL_SOLID,VAL_CONNECTED_POINTS,VAL_DK_GREEN);
			
			//free(fereastra);
}
void Blackman(double input[],int noElements,double output[],int start){
	double *coef=0;
	coef=(double*)calloc(noElements,sizeof(double));
	for(int i=1;i<=noElements;i++){
	coef[i-1] = 0.42 - 0.5 * cos(2 * PI * i/(noElements - 1)) + 0.08 * cos(4 * PI * i/(noElements - 1));
	}
	for(int i=0;i<noElements;i++)
	{
		output[i]=coef[i]*input[i+start];
	}
	
}
void BlackmanHarris(double input[],int noElements,double output[],int start){
	double *coef=0;
	coef=(double*)calloc(noElements,sizeof(double));
	for(int i=1;i<=noElements;i++){
	coef[i-1] = 0.42323 - 0.49755 * cos(2 * PI * i/(noElements - 1)) + 0.07922 * cos(4 * PI * i/(noElements - 1));
	}
	for(int i=0;i<noElements;i++)
	{
		output[i]=coef[i]*input[i+start];
	}
	
}
