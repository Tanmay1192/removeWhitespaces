#include <stdio.h>
#include <string.h>
#include <ctype.h>

// To check presence of the MIPSPro 7.2 or later compilers. And check for c99 standard as restrict is supported in c99
#if ( _COMPILER_VERSION >= 720 && __STDC_VERSION__ == 199901L)
  #define RESTRICT restrict
#else
  #define RESTRICT
#endif



#define FROM_START         0x1
#define FROM_END           0x2
#define ALL                0x7

#define NOT_TRIM_ORIGNAL   1
#define TRIM_ORIGNAL       2

char *remove_whitespaces(char* RESTRICT string, char* RESTRICT out_string, char operation, char tampering_mode)
{
  NDTL4(trace_log_key, NULL, TL_INFO, "Method called");
  if(string == NULL)//|| tampering_mode != NOT_TRIM_ORIGNAL || tampering_mode != TRIM_ORIGNAL)
  { 
    NDTL0(trace_log_key, NULL, TL_ERROR, "Invalid input is passed");
    return NULL; 
  } 
  int i;
  int string_len = (int)(strlen(string));
  RESTRICT int last_count = string_len - 1;
  RESTRICT int start_count = 0;
  char first_char_found = 0;
  char last_char_found = 1;
  char* RESTRICT untrim = NULL;

  if((tampering_mode & NOT_TRIM_ORIGNAL) && out_string != NULL)
  {
    if(sizeof(out_string) < sizeof(string))
    {
      NDTL0(trace_log_key, NULL, TL_ERROR, "Second field pass i.e output buffer is of less size than original");
      return NULL;
    }
    else
    {
      strcpy(out_string, string);
      untrim = out_string;
    }
  }

  else if(tampering_mode & TRIM_ORIGNAL)
    untrim = string;
      else
  {
    NDTL0(trace_log_key, NULL, TL_ERROR, "Check 2nd and 4th argument field");
    return NULL;
  }

  if(operation != FROM_START && operation != FROM_END && operation != ALL && operation != (FROM_END|FROM_START))
    operation = ALL;

  for(i = 0; i < string_len && string[i] != '\0'; i++)
  {
    if(operation != ALL && (operation & FROM_END))
    {
      while(isspace(string[last_count]))
      {
        last_count--;
        continue;
      }
      if(last_char_found)
      {
        untrim[last_count + 1] = '\0';
        last_char_found = 0;
      }
    }

    if(operation != ALL && (operation & FROM_START))
    {
      if(!isspace(string[i]))
        first_char_found = 1;

      if(first_char_found == 1)
        untrim[start_count++] = untrim[i];
    }

    if((operation ==  ALL) && !isspace(string[i]))
      untrim[start_count++] = string[i];
  }

  if(operation == FROM_START || operation == ALL || operation == (FROM_START|FROM_END))
     untrim[start_count] = '\0';

  NDTL4(trace_log_key, NULL, TL_INFO, "Method Exit");
  return untrim;
}


#ifdef TEST
int main(void)
{
  char str[256];
  char out_str[256];
  char *ptr = NULL;
 
  printf("Enter any string:\n");
  gets(str);
  
  printf("Going to remove whitespaces\n");
  ptr =  remove_whitespaces(str, NULL, FROM_START|FROM_END, TRIM_ORIGNAL);
  printf("final string is : [%s]",str);
  printf("function return: [%s]\n", ptr);
  return 0;
}
#endif
