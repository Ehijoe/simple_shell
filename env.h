#ifndef ENV_H
#define ENV_H

void env(char **tokenized_command __attribute__((unused)), shell_t *p);
char *get_env(char *key);
int set_env(char *key, char *val);
int unset_env(char *key);

#endif