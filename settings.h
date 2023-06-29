#ifndef SETTINGS_H
#define SETTINGS_H

void sizeConsole();
void sizeFont();
void colorBackground();
void setConsoleFontSize(int size);

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 24
#define MAX_MESSAGES 4

void sizeConsole(){
    HWND console = GetConsoleWindow();
    RECT rect;
    GetWindowRect(console, &rect);

    // Define el nuevo tamaño de la ventana en píxeles
    MoveWindow(console, rect.left, rect.top, 1300, 700, TRUE);
}

void sizeFont(){
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_FONT_INFOEX fontInfo;
    GetCurrentConsoleFontEx(console, FALSE, &fontInfo);

    // Define el nuevo tamaño de la letra
    fontInfo.dwFontSize.X = 20;
    fontInfo.dwFontSize.Y = 26;
    SetCurrentConsoleFontEx(console, FALSE, &fontInfo);
}

void colorBackground(){
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    // Define el color de fondo
    SetConsoleTextAttribute(console, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
}

void messageEfect(){
    system("cls");

    char *messages[] = {
        "CREDITOS:",
        ">> ANGEL GABRIEL BENITEZ",
        ">> AXEL LEDESMA"
    };

    int num_messages = sizeof(messages) / sizeof(messages[0]);

    int message_lengths[MAX_MESSAGES];
    int x[MAX_MESSAGES];
    int y[MAX_MESSAGES];

    // Inicializar las posiciones de los mensajes
    for (int i = 0; i < num_messages; i++) {
        message_lengths[i] = strlen(messages[i]);
        x[i] = SCREEN_WIDTH / 2 - message_lengths[i] / 2;   // Posición inicial del mensaje en el centro
        y[i] = i + 1;                                       // Posición vertical inicial del mensaje
    }

    int all_messages_fallen = 0;

    while (!all_messages_fallen) {
        printf("\033[2J\033[1;1H"); // Limpia la pantalla y posiciona el cursor en (1, 1)
        
        // Imprimir los mensajes y actualizar sus posiciones
        for (int i = 0; i < num_messages; i++) {
            if (y[i] <= SCREEN_HEIGHT) {
                printf("\033[%d;%dH%s", y[i], x[i], messages[i]); // Posiciona el cursor en (x, y) y muestra el mensaje
                y[i]++; // Incrementa la posición vertical del mensaje para simular su caída
            }
        }

        fflush(stdout); // Limpia el búfer de salida para mostrar inmediatamente los mensajes

        pause(1); // Pausa de 100,000 microsegundos (0.1 segundos) entre cada iteración

        all_messages_fallen = 1;

        // Verificar si todos los mensajes han caído
        for (int i = 0; i < num_messages; i++) {
            if (y[i] <= SCREEN_HEIGHT) {
                all_messages_fallen = 0;
                break;
            }
        }
    }
}

void setConsoleFontSize(int size) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);

    fontInfo.dwFontSize.Y = size; // Tamaño de la letra en puntos

    SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
}

#endif