#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <limits.h>
void imprimir_indentacion(int nivel) {
    for (int i = 0; i < nivel; i++) {
        printf("   ");
    }
}
void draw_tree(const char *path, int indent) {
    struct dirent *entry;
    DIR *dir = opendir(path);
    if (!dir) 
        return;
    
    while ((entry = readdir(dir)) != NULL) {
        // Ignorar los directorios "." y ".." para evitar bucles infinitos
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        // Construir la ruta completa para verificar si es un directorio
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        struct stat st;
        if (lstat(full_path, &st) == -1) {
            continue; // Error al leer datos del archivo, pasamos al siguiente
        }
	if (S_ISLNK(st.st_mode)) {
            imprimir_indentacion(indent);
            printf("|-- \033[1;36m%s\033[0m -> [Enlace Simolico Protegido]\n", entry->d_name);
            continue;
        }
        if (S_ISDIR(st.st_mode)) {
            imprimir_indentacion(indent);
		printf("|-- \033[1;34m%s/\033[0m\n", entry->d_name);
            
           draw_tree(full_path,indent + 1);
        } 
  
        else {
            imprimir_indentacion(indent);
            printf("|-- %s\n", entry->d_name);
        }    
    }
    closedir(dir);
}





int main(int argc, char *argv[]) {
    const char *start_dir = (argc > 1) ? argv[1] : ".";
    
   printf("%s\n", start_dir);
    draw_tree(start_dir, 0);
    

   return 0;
}
