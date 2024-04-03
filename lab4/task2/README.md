# Run on Windows
```bash
cmake -S . -B build
cmake --build build --config Release
.\build\bin\Release\BITMAP_Annealing.exe
```

# Comparision of the results
Bitmaps with faster cooling rate have more noise and they are less organized. With change of density of the bitmap, the results are more visible. The higher the density, the more noise is visible. The lower the density, the more organized the bitmap is. 