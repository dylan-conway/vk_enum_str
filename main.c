#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(){

    FILE* outf = fopen("vk_enum_str.h", "w");
    FILE* inf = fopen("C:/VulkanSDK/1.2.176.1/Include/vulkan/vulkan_core.h", "r");
    fprintf(outf, "#ifndef _VK_ENUM_STR_H_\n#define _VK_ENUM_STR_H_\n\n");
    fprintf(outf, "#include <vulkan/vulkan.h>\n\n");

    // Find largest word
    int max = 0;
    int length = 0;
    char c = 0;

    do{
        c = getc(inf);
        while(c != EOF && c != ' ' && c != '\n' && c != '\t'){
            length += 1;
            c = getc(inf);
        }
        if(length > max) max = length;
        length = 0;
    } while(c != EOF);
    rewind(inf);


    char* word = malloc(sizeof(char) * max + 1);
    char* value = malloc(sizeof(char) * max + 1);
    int value_length = 0;
    memset(word, '\0', max + 1);
    memset(value, '\0', max + 1);

    // Identify enums and write their names and possible values to file
    do{
        c = getc(inf);
        while(c != EOF && c != ' ' && c != '\n' && c != '\t'){
            word[length] = c;
            length += 1;
            c = getc(inf);
        }
        if(strcmp("enum", word) == 0){
            memset(word, '\0', max + 1);
            length = 0;
            while((c == ' ' || c == '\n' || c == '\t') && c != EOF){
                c = getc(inf);
            }
            while(c != ' ' && c != '\n' && c != '\t' && c != EOF){
                word[length] = c;
                length += 1;
                c = getc(inf);
            }
            fprintf(outf, "#define STR_VK");
            for(int i = 2; i < length; i ++){
                if(islower(word[i - 1]) && isupper(word[i])){
                    fprintf(outf, "_");
                }
                fprintf(outf, "%c", toupper(word[i]));
            }
            fprintf(outf, "(x) (\\\n");
            memset(word, '\0', max + 1);
            length = 0;
            do{
                while((c == ' ' || c == '\n' || c == '\t' || c == '{') && c != EOF){
                    c = getc(inf);
                }
                while(c != ' ' && c != '\n' && c != '\t' && c != EOF){
                    word[length] = c;
                    length += 1;
                    c = getc(inf);
                }
                // Catch ifdef's and endif's 
                if(word[0] == '#') {
                    while(c != '\n'){
                        c = getc(inf);
                    }
                    memset(word, '\0', max + 1);
                    length = 0;
                    continue;
                }
                while(c == ' ' || c == '='){
                    c = getc(inf);
                }
                while(c != ' ' && c != '\n' && c != '\t' && c != ',' && c != EOF){
                    value[value_length] = c;
                    value_length += 1;
                    c = getc(inf);
                }
                int bad = 0;
                for(int i = 0; i < value_length; i ++){
                    if(!isxdigit(value[i]) && value[i] != 'x' && value[i] != '-'){
                        bad = 1;
                        break;
                    }
                }
                if(!bad) fprintf(outf, "\tx==%s?\"%s\":\\\n", value, word + 3);
                memset(word, '\0', max + 1);
                length = 0;
                memset(value, '\0', max + 1);
                value_length = 0;
                while(c != '\n'){
                    c = getc(inf);
                }
                c = getc(inf);
                while((c == ' ' || c == '\n' || c == '\t') && c != EOF){
                    c = getc(inf);
                }
            } while(c != '}');

            fprintf(outf, "\t\"ENUM_UNKNOWN\")\n\n");
        }
        memset(word, '\0', max + 1);
        length = 0;
    } while(c != EOF);
    
    fprintf(outf, "#endif\n");

    free(word);
    fclose(inf);
    fclose(outf);

    return 0;
}
