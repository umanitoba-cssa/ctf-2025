# Picture To ASCII
- Revision 0
- Binary Exploitation

## Description
You stumble upon a program that converts any image into ASCII art. Part of the implementation takes into account the **luminance** of a pixel which is calculated as $r * 0.2126 + g * 0.7152 + b * 0.0722$ where r, g, b are the respective rgb components. You **round up** each weighted colour component before adding them up. This is done to as to find the appropiate greyscale value. You also don't want to luminate every pixel so if the red > 250 and green > 250 and blue > 240. It's considered bright enough to not need to run the luminance formula.

This program runs its own executable so you will have to check if you downloaded the correct version. Currently only Mac (or unix) works but will add for Windows and Linux soon.

## Hint
You could test every photo in your phone to try to crash the program or use a painting software (Paint.NET for Windows or Paint S for Mac).

## Solution
Simply create an image that is barely below the luminance threshold (255, 255, 239) and the program would have luminance that is more than 255. This can't happen so the program panics and prints the flag (but no ASCII photo :().

> The reason why these values were chosen is so that it is much harder to randomly upload a standard photo and get the secret message without *intentionally* submitting an edge case.

## Flag
`cssactf{Its_Always_A_Brighter_Day}`
