#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>      
#include <sys/wait.h>

#define MAX_LEN 512
#define MAX_ARGS 128

void exec_cmd(char *cmd) {
    char *args[MAX_ARGS];
    char *token;
    int i = 0;

    // Tokenize the command line input
    token = strtok(cmd, " \n");
    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, " \n");
    }
    args[i] = NULL;  // Null-terminate the argument list

    if (i == 0) {
        return; // Empty command
    }

    // Check if the command is a full path or needs to be prefixed
    char command[MAX_LEN];
    if (args[0][0] != '/') {
        snprintf(command, sizeof(command), "/bin/%s", args[0]); // Change this to the appropriate directory
    } else {
        strncpy(command, args[0], sizeof(command));
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return;
    }

    if (pid == 0) {  // Child process
        if (execv(command, args) == -1) {
            perror("Command execution failed");
            exit(EXIT_FAILURE);
        }
    } else {
    // Parent process, wait for the child to finish
    wait(NULL);
}
}

// Function to process and execute multiple commands
void proc_cmd(char *input) {
    char *cmd = strtok(input, ";");
    pid_t pids[MAX_ARGS]; // Store child process IDs
    int num_cmds = 0;

    while (cmd != NULL) {
        // Remove leading and trailing whitespace
        char *start = cmd;
        while (*start == ' ') start++;
        char *end = start + strlen(start) - 1;
        while (end > start && (*end == ' ' || *end == '\n')) end--;
        *(end + 1) = '\0'; // Null-terminate the command

        // Echo the command
        if (strlen(start) > 0) {
            printf("Executing: %s\n", start);
            exec_cmd(start);
            //pids[num_cmds++] = fork();
        }

        cmd = strtok(NULL, ";");
    }

    // Wait for all child processes to finish
    for (int i = 0; i < num_cmds; i++) {
        if (pids[i] > 0) {
            waitpid(pids[i], NULL, 0);
        }
    }
}

// Function to process the batch file or interactive commands
void handle_input(FILE *input_stream) {
    char cmd[MAX_LEN];

    while (fgets(cmd, sizeof(cmd), input_stream) != NULL) {
        // Remove any trailing newline or spaces
        cmd[strcspn(cmd, "\n")] = 0;

        // Skip empty commands
        if (strlen(cmd) == 0) {
            continue;  // Skip to next command
        }

        // Handle quit command
        if (strncmp(cmd, "quit", 4) == 0 && strlen(cmd) == 4) {
            break;
        }

        // Process and execute commands
        proc_cmd(cmd);
    }
}

int main(int argc, char *argv[]) {
    if (argc > 2) {
        fprintf(stderr, "Usage: %s [batchFile]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    // If a batch file is provided
    if (argc == 2) {
        FILE *batch_file = fopen(argv[1], "r");
        if (!batch_file) {
            fprintf(stderr, "Error: Batch file '%s' does not exist or cannot be opened.\n", argv[1]);
            exit(EXIT_FAILURE);
    }

    char command_dir[1024];
    // Read the first line of the batch file for the directory path
    if (fgets(command_dir, sizeof(command_dir), batch_file) == NULL) {
        fprintf(stderr, "Error: Batch file is empty or invalid.\n");
        fclose(batch_file);
        exit(EXIT_FAILURE);
    }

    // Remove the newline character from the directory path
    command_dir[strcspn(command_dir, "\n")] = 0;

    // Check if the directory path exists
    if (access(command_dir, F_OK) == -1) {
        fprintf(stderr, "Error: Directory path '%s' does not exist.\n", command_dir);
        fclose(batch_file);
        exit(EXIT_FAILURE);
    }

    printf("Command directory set to: %s\n", command_dir);

    // Process the remaining commands in the batch file
    char command[1024];
    while (fgets(command, sizeof(command), batch_file) != NULL) {
        // Remove newline character
        command[strcspn(command, "\n")] = 0;

        // Skip empty lines
        if (strlen(command) == 0) continue;

        printf("Read command from batch file: %s\n", command);

        // Prepend the directory path to the command
        char full_command[2048];
        snprintf(full_command, sizeof(full_command), "%s/%s", command_dir, command);

        // Print the command being executed
        printf("Executing: %s\n", full_command);

        // Execute the command using the full path
        exec_cmd(full_command);  // Assuming you have an execute_command() function
    }

    fclose(batch_file);
    }else {
        // Interactive mode
        printf("Entering interactive mode. Type 'quit' to exit.\n");
        while (1) {
            printf("myshell> ");
            char input[MAX_LEN];
            if (fgets(input, sizeof(input), stdin) == NULL) {
                break; // EOF or error
            }

            // Remove trailing newline
            input[strcspn(input, "\n")] = 0;

            // Skip empty commands
            if (strlen(input) == 0) {
                continue;
            }

            // Handle quit command
            if (strncmp(input, "quit", 4) == 0 && strlen(input) == 4) {
                break;
            }

            // Process and execute commands
            proc_cmd(input);
        }
    }

    return 0;
}

