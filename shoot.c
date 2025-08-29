#include "lazer.h"

typedef void (*missile_fn)(const char* target);

void animate_wave(const char *str, int delay_us) {
    int len = strlen(str);
    char buffer[len + 1];
    strcpy(buffer, str);

    const char *green = "\033[32m";
    const char *reset = "\033[0m";
    fflush(stdout);

    for (int i = 0; i <= len; i++) {
        printf("\033[K");
        printf("\r%s%.*s%s", green, i, buffer, reset);
        fflush(stdout);
        usleep(delay_us);
    }
}

void print_help(const char *prog_name) {
    printf("Usage: %s <missile.so> <target> \n[-h] OR --list-ammo *wink* \n", prog_name);
    printf("\nLazerbeam: A modular file attack launcher\n");
    printf("Launches the specified missile from ammo/ to attack the target file.\n");
    printf("Options:\n");
    printf("  -h           Show this help message\n");
    printf("  --list-ammo  List available missiles\n");
    printf("Available missiles:\n");

    DIR *dir = opendir("ammo");
    if (!dir) {
        printf("  (No missiles found in ammo/)\n");
    } else {
        struct dirent *entry;
        while ((entry = readdir(dir))) {
            if (strstr(entry->d_name, ".so")) {
                printf("  - %s\n", entry->d_name);
            }
        }
        closedir(dir);
    }
    printf("\nNote: Always use on test files in a controlled lab environment!\n");
}

void list_ammo() {
    printf("Available missiles:\n");
    DIR *dir = opendir("ammo");
    if (!dir) {
        printf("  (No missiles found in ammo/)\n");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir))) {
        if (strstr(entry->d_name, ".so")) {
            printf("  - %s\n", entry->d_name);
        }
    }
    closedir(dir);
}

void draw_art(const char *filename, int delay_us) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        fprintf(stderr, "Warning: Could not open %s\n", filename);
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), f)) {
        line[strcspn(line, "\n")] = '\0';
        if (strlen(line) > 0) {
            animate_wave(line, delay_us);
            printf("\n");
            fflush(stdout);
        }
    }

    fclose(f);
}

int main(int argc, char **argv) {
    if (argc == 2) {
        if (strcmp(argv[1], "-h") == 0) {
            print_help(argv[0]);
            return 0;
        }
        if (strcmp(argv[1], "--list-ammo") == 0) {
            list_ammo();
            return 0;
        }
    }

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <missile.so> <target> \n[-h] OR --list-ammo *wink* \n", argv[0]);
        return 1;
    }

    const char *missile = argv[1];
    const char *target = argv[2];

    char missile_path[256];
    if (strstr(missile, "ammo/") != missile) {
        snprintf(missile_path, sizeof(missile_path), "ammo/%s", missile);
    } else {
        strncpy(missile_path, missile, sizeof(missile_path));
        missile_path[sizeof(missile_path) - 1] = '\0';
    }

    void *handle = dlopen(missile_path, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "dlopen error: %s\n", dlerror());
        return 1;
    }

    missile_fn fire = (missile_fn)dlsym(handle, "run");
    if (!fire) {
        fprintf(stderr, "dlsym error: %s\n", dlerror());
        dlclose(handle);
        return 1;
    }
    draw_art("art/art.art", 1000);
    printf("[Lazerbeam] Firing %s at %s...\n", missile_path, target);
    animate_wave("LASER SHOTS LUL!!\n", 120000);
    fire(target);
    dlclose(handle);
    printf("exiting...");
    fflush(stdout);
    sleep(1);
    return 0;
}
