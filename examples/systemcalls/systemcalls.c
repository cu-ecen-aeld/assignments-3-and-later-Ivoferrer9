#include "systemcalls.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdarg.h>

/**
 * @param cmd the command to execute with system()
 * @return true if the command in @param cmd was executed
 *   successfully using the system() call, false if an error occurred,
 *   either in invocation of the system() call, or if a non-zero return
 *   value was returned by the command issued in @param cmd.
 */
bool do_system(const char *cmd)
{
    // Execute the system call
    int ret = system(cmd);

    // Return true if the system call was successful (i.e., ret == 0)
    return (ret == 0);
}

/**
 * @param count - The number of variables passed to the function. The variables are the command to execute,
 * followed by arguments to pass to the command.
 * Since exec() does not perform path expansion, the command to execute needs
 * to be an absolute path.
 * @param ... - A list of 1 or more arguments after the @param count argument.
 * The first is always the full path to the command to execute with execv().
 * The remaining arguments are a list of arguments to pass to the command in execv().
 * @return true if the command @param ... with arguments @param arguments were executed successfully
 *   using the execv() call, false if an error occurred, either in invocation of the
 *   fork, waitpid, or execv() command, or if a non-zero return value was returned
 *   by the command issued in @param arguments with the specified arguments.
 */
bool do_exec(int count, ...)
{
    va_list args;
    va_start(args, count);

    char *command[count + 1];
    for (int i = 0; i < count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL; // NULL-terminate the array of arguments

    va_end(args);

    // Create a new process
    pid_t pid = fork();

    if (pid < 0)
    {
        // Fork failed
        return false;
    }
    else if (pid == 0)
    {
        // In the child process
        execv(command[0], command); // Execute the command
        exit(1); // If execv fails, exit with error
    }
    else
    {
        // In the parent process
        int status;
        waitpid(pid, &status, 0); // Wait for the child process to finish

        // Return true if the child process exited successfully
        return (WIFEXITED(status) && WEXITSTATUS(status) == 0);
    }
}

/**
 * @param outputfile - The full path to the file to write with command output.
 *   This file will be closed at completion of the function call.
 * @param count - The number of variables passed to the function.
 * @param ... - A list of 1 or more arguments after the @param count argument.
 *   The first is always the full path to the command to execute with execv().
 *   The remaining arguments are a list of arguments to pass to the command in execv().
 * @return true if the command @param ... with arguments @param arguments were executed successfully
 *   using the execv() call and the output was redirected to the file specified by @param outputfile,
 *   false if an error occurred, either in invocation of the fork, waitpid, or execv() command,
 *   or if a non-zero return value was returned by the command issued in @param arguments with
 *   the specified arguments.
 */
bool do_exec_redirect(const char *outputfile, int count, ...)
{
    va_list args;
    va_start(args, count);

    char *command[count + 1];
    for (int i = 0; i < count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL; // NULL-terminate the array of arguments

    va_end(args);

    // Create a new process
    pid_t pid = fork();

    if (pid < 0)
    {
        // Fork failed
        return false;
    }
    else if (pid == 0)
    {
        // In the child process

        // Open the file for writing
        FILE *output = fopen(outputfile, "w");
        if (!output)
        {
            exit(1); // Exit if file cannot be opened
        }

        // Redirect standard output to the file
        dup2(fileno(output), STDOUT_FILENO);

        execv(command[0], command); // Execute the command
        exit(1); // If execv fails, exit with error
    }
    else
    {
        // In the parent process
        int status;
        waitpid(pid, &status, 0); // Wait for the child process to finish

        // Return true if the child process exited successfully
        return (WIFEXITED(status) && WEXITSTATUS(status) == 0);
    }
}

