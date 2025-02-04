# Simple frame limiter demo
# Copyright 2022 Jon Ripley

# Initialise constants
# 0 0 (esc) (lsb) 3 8 ; 5 m Hello frame limiter. (lf)
+++++++++++++++[>>++>++++++>+++>++++>++++>++++>+++++++>+++++>+++++++>+++++++>+++
++++>+++++++>++>+++++++>++++++++>++++++>+++++++>+++++++>++>+++++++>+++++++>+++++
++>+++++++>++++++++>+++++++>++++++++>+++>+[<]<-]>>--->+>++++++>---->->------->++
++>--->---->+++>+++>++++++>++>--->------>+++++++>++++>---->++>+++>>++++>>---->--
-->------>+>-----

# Variables 
# 0 m n

# n = 1
>>+
[
  # Print (lsb)(esc)H
  <<<[<]>.>.>>>>>>.

  # m = 25
  [>]>[-]+++++++++++++++++++++++++
  [
    # Print (lsb)(esc)38;5;
    <<[<]>.>.>.>.>.>.<.
    
    # Print n
    [>]>>>>++++++++++<<[->+>-[>+>>]>[+[-<+>]>+>>]<<<<<<]>>[-]>>>++++++++++<[->-[>+>>
    ]>[+[-    <+>]>+>>]<<<<<]>[-]>>[>++++++[-<++++++++>]<.<<+>+>[-]]<[<[->-<]++++++[
    ->++++++++<]>.[-]]<<++++++[-<++++++++>]<.[-]<<[-<+>]<

    # Print mHello frame limiter(dot)
    <<<[<]>>>>>>>[.>]

    # Decrement m 
    >-
  ]
  Increment n
  >+
]
