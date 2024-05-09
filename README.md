# Minishell

This is the first group project in the 42 Core curriculum.
In this project, we created our simple shell.

## Requirements

Here are the functionalities we implemented:

• Display a prompt when waiting for a new command.

• Have a working history.

• Search and launch the right executable (based on the PATH variable or using a relative or an absolute path).

• Handle ’ (single quote).

• Handle " (double quote).

• Implement redirections:
◦   < should redirect input.
◦   > should redirect output.
◦   << should be given a delimiter, then read the input until a line containing the
delimiter is seen. However, it doesn’t have to update the history!
◦   >> should redirect output in append mode.

• Implement pipes.

• Handle environment variables.

• Handle $? which should expand to the exit status of the most recently executed
foreground pipeline.

• Handle ctrl-C, ctrl-D, and ctrl-\ which should behave like in bash.

• Builtins:
◦   echo with option -n
◦   cd with only a relative or absolute path
◦   pwd with no options
◦   export with no options
◦   unset with no options
◦   env with no options or arguments
◦   exit with no options

## Implementation

The project was split into 2 parts: parsing and execution
Parsing:
- Tokenizer and lexer: We get the command and create a linked list of tokens. Each token will have a type based on its value.
- Expander: Expand the environment variables to their values, remove quotes, and expand $? to the last exit status.
- Create command list: We create a linked list of all the commands. Each command will contain
    - The command to execute
    - A linked list of input redirections (each with a type that indicates < or <<)
    - A linked list of output redirections (each with a type that indicates > or >>)
    - A pointer to the next command
    - 
Once this is done, we can do the execution part and execute each command.

## How to run

make

./minishell

To run and check for memory leaks, execute the following:

valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all ./minishell

Then type any command, as if you were in a bash shell and have fun!






