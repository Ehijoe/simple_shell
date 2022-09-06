#ifndef ENV_H
#define ENV_H

char *get_env(char *key, char **environ);
int set_env(char *key, char *val, char ***env);
int unset_env(char *key, char ***env);
int is_valid_key(char *key);
int startsWith(char *s, char *ndl);

#endif
