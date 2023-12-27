#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/raylib.h"

char *code =
    "#include <stdio.h>\n"
    "#include <stdlib.h>\n"
    "\n"
    "\\\\this is a comment\n"
    "int main(int argc, char **argv) {\n"
    "\tprintf(\"hello world\n\");\n"
    "\treturn 0;\n"
    "}"
;

typedef struct {
    Color bg;
    Color text;
} Scheme;

int Hex2Int(char h) {
    if(h >= '0' && h <= '9') {
        return h - '0';
    }

    if(h >= 'a' && h <= 'f') {
        return 10 + h - 'a';
    }
    
    if (h >= 'A' && h <= 'F') {
        return 10 + h - 'A'; 
    }
    return -1;
}

Color Hex2Color(char *hex) {
    Color c = {.a = 0xff};
    c.r = Hex2Int(hex[0]) * 16 + Hex2Int(hex[1]);
    c.g = Hex2Int(hex[2]) * 16 + Hex2Int(hex[3]);
    c.b = Hex2Int(hex[4]) * 16 + Hex2Int(hex[5]);
    return c;
}

Scheme LoadConfig(const char *filepath) {
    Scheme sc;
    char target[64];
    char color[64];
    
    FILE *fp = fopen(filepath, "r");
    if (fp == NULL) {
        printf("couldn't open the scheme file '%s'\n", filepath);
        exit(EXIT_FAILURE);
    }
    
    while(fscanf(fp, "%s #%s", target, color) == 2) {
        if(strcmp(target, "background") == 0) {
            sc.bg = Hex2Color(color);
        }

        if(strcmp(target, "text") == 0) {
            sc.text = Hex2Color(color);
        }
    }

    fclose(fp);

    return sc;
}


int main(int argc, char *argv[]) {

    Scheme scheme = LoadConfig("src/config/scheme.txt");
    
    printf("bg = r:%d, g:%d, b:%d\n", scheme.bg.r, scheme.bg.g, scheme.bg.b);
    printf("text = r:%d, g:%d, b:%d\n", scheme.text.r, scheme.text.g, scheme.text.b);

    char *window_title = "Code Schemer";
    InitWindow(640, 480, window_title);

    char *text = "Code Schemer";
    int font_size = 20;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(scheme.bg);
        DrawText(
            code, 
            GetScreenWidth()/2 - MeasureText(text, font_size)/2, 
            GetScreenHeight()/2 - font_size/2, 
            font_size, 
            scheme.text
        );
        EndDrawing();
    }

    return 0;
}


















