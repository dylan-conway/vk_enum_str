Convert Vulkan enums to strings

## Example
```c
#include "vk_enum_str.h"

// ...

VkResult result = vkCreateInstance(&info, NULL, &instance);
printf("%s\n", STR_VK_RESULT(result));

// ...

VkPresentModeKHR present_mode = ChoosePresentMode();
printf("%s\n", STR_VK_PRESENT_MODE_KHR(present_mode));

// ...
```

## Naming
```c
VkEnumTypeName --> STR_VK_ENUM_TYPE_NAME()
```

