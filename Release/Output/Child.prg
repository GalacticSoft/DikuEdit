>act_prog p pokes you in the~
if isnpc($n)
   chuckle
   poke $n
else
   if level($n) <= 5
   or isgood($n)
      tell $n I would rather you didnt poke me.
   else
      if level($n)>15
         scream
         say Ya know $n. I hate being poked!!!
         kill $n
         break
      endif
      slap $n
      shout MOMMY!!! $N is poking me.
   endif
endif
~
|
