# myshell
##A simple unix shell.
Ce shell est le résultat d'un projet réalisé à l'école 42 de Paris.
Le code est normé selon la norme C de l'école ce qui explique par exemple qu'aucune fonction de fait plus de 25 lignes et il respecte globalement les standards du C89.

Quelques fonctionnalités:
* Executions de commandes avec leurs paramètres.
* Gestion du PATH et des droits.
* Gestion des erreurs et de la valeur de retour des commandes.
* Gestion des opérateurs de redirectino : ">", ">>", "<, des heredoc, des pipes et de l’aggrégation de file descriptors
* Gestion des opérateurs logiques "&&" et "||" ainsi que du séparateur ";".
* Gestion des inhibiteurs """ (double quote), "’" (simple quote) et "\" (backslash).
* Gestion de la subtitution de commande avec les backquotes "`".
* Gestion des sous shells avec les opérateurs "()".
* Gestion de l'expansion des variables d'environnement.
* Gestion des alias.
* Commandes builtin: alias, unalias, cd, echo, env, exit, hash, history, setenv, unsetenv avec leurs options POSIX.
* Édition de ligne avec ses touches d'éditions et la recherche dans l'historique des commandes.
* Support de l'édition de ligne dans les terminaux: xterm, xterm new, vt100, linux, ansi, rxvt et dérivés.
* Completion dynamique pour les commandes, les fichiers, les dossiers et les variables d'environnement.
* Support du Job control et ses builtins job, fg et bg, et l’operateur "&".
* Support des fichiers en entrée.
* Table de hash pour les commandes du PATH.
* Fichier de configuration: ~/.42shrc

Compile avec clang sous macOS ainsi qu'avec GCC sous linux avec quelques ajustements.