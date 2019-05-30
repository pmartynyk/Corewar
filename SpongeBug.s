.name			"SpongeBug"
.comment		"Who lives in the compiler down in the code? 
SpongeBug SegfaultPants! 
Lagging and quitting segfaulting is he? 
SpongeBug SegfaultPants! 
Who works 1 of 10 times you run him in sh? 
SpongeBug SegfaultPants! 
So put in printf and try to break free! 
SpongeBug SegfaultPants! 
Ready? 
SpongeBug SegfaultPants! 
SpongeBug SegfaultPants! 
SpongeBug SegfaultPants! 
SpongeBuuuuuuug SegfaultPaaaaaaaants!" 

live:
	live %0

while:
	fork %-10
	lfork %10
	ld 0, r1
	st r1, 50
	ld 0, r1
	zjmp %:live
