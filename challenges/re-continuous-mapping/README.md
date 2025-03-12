# Continious Mapping

## Description

The suspect got leaked slides from Comp1020 and learned about interfaces and seperate compilation. Doesn't mean its a good job

## Solution

Each letter gets mapped to another letter in an array. So it should be fairly simple to draw a graph where each letter goes and simply follow through the path it makes. 

There are two components, one is a cycle and another is a K3 and letters branching from P 

And the amount of the letters that goes through follows a simple modular system and should be fairly straighforward. (there is a off by one error that I was too lazy to resolve)

Your password can't have the same character as the output in the same position. And this is an issue for P as it is a triangle. So you simply start at D to resolve it
