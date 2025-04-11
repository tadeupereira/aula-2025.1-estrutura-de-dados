#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "validacoes.h"

int validarData(const char *data) {
    if (strlen(data) != 10) return 0;
    if (data[2] != '/' || data[5] != '/') return 0;

    char diaStr[3], mesStr[3], anoStr[5];
    strncpy(diaStr, data, 2);
    diaStr[2] = '\0';
    strncpy(mesStr, data + 3, 2);
    mesStr[2] = '\0';
    strncpy(anoStr, data + 6, 4);
    anoStr[4] = '\0';

    int dia = atoi(diaStr);
    int mes = atoi(mesStr);
    int ano = atoi(anoStr);

    if (dia <= 0 || mes <= 0 || ano <= 0 || mes > 12 || dia > 31) return 0;

    int diasNoMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
        diasNoMes[1] = 29;
    }
    if (dia > diasNoMes[mes - 1]) return 0;

    time_t agora = time(NULL);
    struct tm *atual = localtime(&agora);

    int anoAtual = atual->tm_year + 1900;
    int mesAtual = atual->tm_mon + 1;
    int diaAtual = atual->tm_mday;

    if (ano < anoAtual) return 0;
    if (ano == anoAtual && mes < mesAtual) return 0;
    if (ano == anoAtual && mes == mesAtual && dia < diaAtual) return 0;

    return 1;
}

int validarHorario(const char *horario) {
    if (strlen(horario) != 5 || horario[2] != ':') return 0;

    char horaStr[3], minutoStr[3];
    strncpy(horaStr, horario, 2);
    horaStr[2] = '\0';
    strncpy(minutoStr, horario + 3, 2);
    minutoStr[2] = '\0';

    int hora = atoi(horaStr);
    int minuto = atoi(minutoStr);

    if (hora < 0 || hora > 23 || minuto < 0 || minuto > 59) return 0;

    return 1;
}