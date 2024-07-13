# MINISHELL

Minishell is a 42 project, tasked to recreate a 'mini' version of a Bash shell.
The minishell is able to handle commands and built-ins commands(echo, cd, pwd, export, unset, env, exit), redirections(infile, outfile, heredoc, append redirections) and pipes. It is also able to intepret double and single quotes to expand environment variables when is should. And of course signals handling for ctrl-c, ctrl-d and ctrl-\!


## Authors

- [@terius13](https://www.github.com/terius13)</br>
Handled the Tokenization, Parsing, Pipes, Redirections and Execution.
- [@AlwIkigai](https://www.github.com/AlwIkigai)</br>
Handled the Built-ins(echo, cd, pwd, export, unset, env, exit) and Signals.
