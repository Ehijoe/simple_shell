#ifndef ARGUMENTS_H
#define ARGUMENTS_H

char **parse(char *line);
int is_whitespace(char c);
void del_arglist(char **arglist);

#endif
