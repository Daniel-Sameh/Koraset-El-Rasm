extern COLORREF bgColor;

void load(HWND hwnd) {
    FILE* file = fopen("no2tas.dat", "rb");
    if (!file) {
        std::cerr << "mfe4 file\n";
        return;
    }

    size_t count;
    fread(&count, sizeof(size_t), 1, file); //ygeb el size
    std::vector<no2ta> loadedno2tas(count);
    fread(loadedno2tas.data(), sizeof(no2ta), count, file); //be3ml load ll data fel loadno2tas
    fclose(file);

    HDC hdc = GetDC(hwnd);
    //for loop wa set kol no2ta b 7agtah
    for (const no2ta& p : loadedno2tas) {
        SetPixel(hdc, p.x, p.y, p.color);
    }
    ReleaseDC(hwnd, hdc);

}


void save(HWND hwnd) {
    RECT rect;
    GetClientRect(hwnd, &rect);
    int width  = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    HDC hdc = GetDC(hwnd);
    HDC memDC = CreateCompatibleDC(hdc);

    BITMAPINFO bmi = {};
    bmi.bmiHeader.biSize= sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth= width;
    bmi.bmiHeader.biHeight= -height;
    bmi.bmiHeader.biPlanes= 1;
    bmi.bmiHeader.biBitCount= 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    void* no2tas = nullptr;
    HBITMAP hbm = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &no2tas, NULL, 0);
    SelectObject(memDC, hbm);
    BitBlt(memDC, 0, 0, width, height, hdc, 0, 0, SRCCOPY);
    //btcopy el window fel bitmap
    ReleaseDC(hwnd, hdc);

    vector<no2ta> saved;

    #pragma omp parallel
    {
        vector<no2ta> local;
        #pragma omp for
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                DWORD raw = ((DWORD*)no2tas)[y * width + x]; //el raw beb2a 1d fa bndrb el y*width 34an n3rf el height
                //el lon bet5zn 00000 00000 000000 wa keda fa el blue be5od awl 8 3l yemen el green tany 8 wa el red talt 8
                BYTE blue  = raw & 0xFF;
                BYTE green = (raw >> 8) & 0xFF;
                BYTE red   = (raw >> 16) & 0xFF;
                COLORREF c = RGB(red, green, blue);


                if (c != bgColor)
                    local.push_back({ x, y, c });
            }
        }
        //bngm3 kolo fel saved da
        #pragma omp critical
        saved.insert(saved.end(), local.begin(), local.end());
    }

    DeleteDC(memDC);
    DeleteObject(hbm);
    //bnsave el data fel file
    FILE* f = fopen("no2tas.dat", "wb");
    if (f) {
        size_t count = saved.size();
        fwrite(&count, sizeof(count), 1, f);
        fwrite(saved.data(), sizeof(no2ta), count, f);
        fclose(f);
    }
}
