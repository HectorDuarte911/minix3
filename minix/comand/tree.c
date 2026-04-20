o.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>

void draw_tree(const char *path, int indent) {
    struct dirent *entry;
    DIR *dir = opendir(path);

    if (!dir) 
        return;
    

    while ((entry = readdir(dir)) != NULL) {
        // Ignorar los directorios "." y ".." para evitar bucles infinitos
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        // Crear la sangria visual
        for (int i = 0; i < indent; i++) {
            printf("   ");
        }

        // Imprimir el nombre del archivo o carpeta
        printf("|-- %s\n", entry->d_name);

        // Construir la ruta completa para verificar si es un directorio
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        struct stat st;
        if (stat(full_path, &st) == 0 && S_ISDIR(st.st_mode)) {
            // Llamada recursiva si es un directorio
            draw_tree(full_path, indent + 1);
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
