#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for the linked list node
typedef struct PathNode {
    char *path;
    struct PathNode *next;
} PathNode;

// Head of the linked list for the pathname environment
PathNode *path_head = NULL;

// Function to display the current pathname environment
void show_path() {
    if (path_head == NULL) {
        printf("Path environment is empty.\n");
        return;
    }
    
    PathNode *current = path_head;
    while (current != NULL) {
        printf("%s", current->path);
        if (current->next != NULL) {
            printf(":");  // Separate paths with colon
        }
        current = current->next;
    }
    printf("\n");
}
// Function to check if a path already exists
int exists_path(char *new_path) {
    PathNode *current = path_head;
    while (current != NULL) {
        if (strcmp(current->path, new_path) == 0) {
            return 1; // Path already exists
        }
        current = current->next;
    }
    return 0; // Path does not exist
}

// Function to append a directory to the pathname environment
void append_path(char *new_path) {
    // Check if the path already exists
    if (exists_path(new_path)) {
        printf("Path '%s' already exists. Not appending.\n", new_path);
        return;
    }

    // Print the debug message only if the path is being appended
    printf("Appending path: %s\n", new_path);  // Debug print

    // Create a new node
    PathNode *new_node = (PathNode *)malloc(sizeof(PathNode));
    if (new_node == NULL) {
        perror("Failed to allocate memory");
        return;
    }
    new_node->path = strdup(new_path);  // Copy the new path
    new_node->next = NULL;

    // If the list is empty, add the new node as the head
    if (path_head == NULL) {
        path_head = new_node;
    } else {
        // Traverse to the end of the list
        PathNode *current = path_head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }

    printf("Path appended successfully.\n");  // Debug print
}

// Function to remove a directory from the pathname environment
void remove_path(char *path_to_remove) {
    PathNode *current = path_head;
    PathNode *previous = NULL;

    printf("Removing path: %s\n", path_to_remove);  // Debug print
    
    while (current != NULL) {
        if (strcmp(current->path, path_to_remove) == 0) {
            // If the node to remove is the head
            if (previous == NULL) {
                path_head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current->path);
            free(current);
            printf("Path removed successfully.\n");  // Debug print
            return;
        }
        previous = current;
        current = current->next;
    }
    // If the path is not found, do nothing
    printf("Path not found, nothing to remove.\n");  // Debug print
}

// Function to handle the "path" command
void handle_path_cmd(char *input) {
    char *token = strtok(input, " ");

    // Check if there's a "+" or "-" argument for modifying the path
    if (token != NULL) {
        token = strtok(NULL, " "); // Get the second token (should be "+" or "-")

        if (token == NULL) {
            show_path();  // No argument, just display the current path
        } else if (token[0] == '+') {
            // Get the new path (after the '+')
            char *new_path = strtok(NULL, " "); // Get the actual path
            if (new_path != NULL) {
                append_path(new_path);  // Append the path
            } else {
                printf("No path provided to append.\n");
            }
        } else if (token[0] == '-') {
            // Get the path to remove (after the '-')
            char *path_to_remove = strtok(NULL, " "); // Get the actual path
            if (path_to_remove != NULL) {
                remove_path(path_to_remove);  // Remove the path
            } else {
                printf("No path provided to remove.\n");
            }
        } else {
            printf("Invalid argument for path command.\n");
        }
    }
}

// Function to run the shell and accept commands
void run_shell() {
    char input[256];

    while (1) {
        printf("myshell> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        // Remove the newline character from the input
        input[strcspn(input, "\n")] = 0;

        // Check if the user entered "path"
        if (strncmp(input, "path", 4) == 0) {
            handle_path_cmd(input);
        } else {
            printf("Command not recognized or no path set.\n");
        }
    }
}

//int main() {
  //  run_shell();
    //return 0;
//}


