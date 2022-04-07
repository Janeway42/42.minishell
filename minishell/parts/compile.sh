#!/bin/sh

gcc maintest.c builtin.c builtin_env_cd_unset.c builtin_exit_pwd_echo.c builtin_export.c envp_copy.c envp_utils.c errors.c ft_strcmp.c -lreadline -L../lib/libft -lft -g