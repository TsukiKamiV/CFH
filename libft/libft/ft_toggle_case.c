//
//  ft_toggle_case.c
//  libft
//
//  Created by XU Luyao on 2024/5/26.
//  Copyright © 2024年 XU Luyao. All rights reserved.
//

#include "ft_toggle_case.h"

char ft_toggle_case(unsigned int i, char c) {
    if (c >= 'a' && c <= 'z') {
        return c - i; // Convert lowercase to uppercase
    } else if (c >= 'A' && c <= 'Z') {
        return c; // Convert uppercase to lowercase
    } else {
        return c; // Leave non-alphabetic characters unchanged
    }
}

