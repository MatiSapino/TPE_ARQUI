#ifndef __COMMANDS_H__
#define __COMMANDS_H__

#include "utils.h"
#include "UserSyscalls.h"

#define COMMAND_AMOUNT 9





void checkCommands(char * command); //Busca el comando ingresado por el usuario
void commandNotFound(char * command);
void help(); //Imprime la lista de comandos
void time(); //Imprime la hora actual
void div0(); //Divide por 0 y genera una excepcion
void invalidOp(); //Genera una excepcion de operacion invalida

#endif /*__COMMANDS_H__*/