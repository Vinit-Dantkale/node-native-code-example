#include <node_api.h>
#include <string.h>

// #define NAPI_CALL(env, call)                                      \
//   do                                                              \
//   {                                                               \
//     napi_status status = (call);                                  \
//     if (status != napi_ok)                                        \
//     {                                                             \
//       const napi_extended_error_info *error_info = NULL;          \
//       napi_get_last_error_info((env), &error_info);               \
//       bool is_pending;                                            \
//       napi_is_exception_pending((env), &is_pending);              \
//       if (!is_pending)                                            \
//       {                                                           \
//         const char *message = (error_info->error_message == NULL) \
//                                   ? "empty error message"         \
//                                   : error_info->error_message;    \
//         napi_throw_error((env), NULL, message);                   \
//         return NULL;                                              \
//       }                                                           \
//     }                                                             \
//   } while (0)

int is_prime(int num)
{
  if (num <= 1)
    return 0;
  for (int i = 2; i <= num / 2; i++)
  {
    if (num % i == 0)
    {
      return 0;
    }
  }
  return 1; //if both failed then num is prime
}

int find_prime(int upper_limit)
{
  int largest_prime;

  for (int i = 2; i <= upper_limit; i++)
  {
    if (is_prime(i))
    {
      largest_prime = i;
    }
  }

  return largest_prime;
}


napi_value FindPrimes(napi_env env, napi_callback_info info)
{
  size_t argc = 1;
  napi_value args[1];
  int64_t upper_limit;
  int64_t largest_prime;
  napi_value output;

  // Extract the arguments passed into the function
  // We pass the expected number of arguments and an array to store the arguments in
  napi_get_cb_info(env, info, &argc, args, NULL, NULL);

  // Convert the arguments provided into int 
  napi_get_value_int64(env, args[0], &upper_limit);

  // Calculate largest prime until the upper_limit
  largest_prime = find_prime(upper_limit);

  // Convert it back into JS value, by passing "napi_value output" by reference
  napi_create_double(env, largest_prime, &output);

  return output;
}

// We define an init function from which we want to return a napi_value
// napi_value forms backbone of all variables in node.js
// In c++ file, JS string, numbers, boolean, functions, objects are all represented by napi value
// init function takes napi_env, and napi_value
napi_value init(napi_env env, napi_value exports)
{
  napi_value find_primes;

  napi_create_function(env, nullptr, 0, FindPrimes, nullptr, &find_primes);

  return find_primes;
}


// We run this function NAPI_MODULE register the module
NAPI_MODULE(NODE_GYP_MODULE_NAME, init);
// named the module with a name, and providing an init function