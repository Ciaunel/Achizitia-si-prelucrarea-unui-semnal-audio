# Achizitia-si-prelucrarea-unui-semnal-audio

## Introducere
   Acest proiect implementează o interfață grafică pentru achiziția unui semnal audio și analiza 
acestuia în domeniul  timp și domeniul frecvență. Semnalul audio achiziționat este o notă muzicală 
pentru care s-a extras un singur canal pentru prelucrarea acestuia.  
   Analiza semnalului s-a făcut prin aplicare de filtre și ferestre, determinarea plajei de valori 
prin calculul histogramei și a valorilor Kurtosis, Skewness, a medianei și a dispersiei și obținerea spectrului  semnalului prin calcularea transformatei Fourier.

## Structura proiectului
- `APD_proiect.c`, `.h`, `.prj`, `.cws` – Codul sursă și fișierele de configurare LabWindows/CVI
- `52.wav` – Fișierul audio utilizat ca semnal de intrare
- `waveData.txt`, `canal1.txt`, `envelope.txt`, `wafelInfo.txt` – Date extrase/intermediare
- `proiect_apd.py` – Script auxiliar pentru analiză (Python)
- `README.md` – Acest fișier
  
## Rulare
 Fișierul poate fi rulat din mediul de lucru LabWindows/CVI după ce vă asigurați că ați adăugat corect toate fișierele și dependențele.
