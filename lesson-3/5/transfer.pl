#PERL转换函数

#!/usr/bin/perl -w
use strict;

#先打开文件
open FD,"abs.c.txt" or die "cna't open file";
my @lines = <FD>;
close FD;

chomp @lines;
s/#.*|^$|^\/\/|^\s*int.*$|^.*else.*$|\}// foreach @lines;
@lines = grep !/^$/, @lines;
unshift @lines,'	.data
VAR0: .ascii "input x:\n\000"
VAR1: .ascii "%d\000"
VAR2: .ascii "the answer is %d\n\000"
	.text
	.global main
	.ent main
main:
addiu $sp,$sp,-64
sw $ra,60($sp)
sw $fp,56($sp)
move $fp,$sp';


foreach(@lines){
	if($_ =~ /printf\(\"input x.*$/){
		$_ = "la \$a0,VAR0\njal printf";
	}elsif($_ =~ /scanf\(\"\%d.*$/){
		$_ = "la \$a0,VAR1\naddiu \$a1,\$fp,52\njal __isoc99_scanf";
	}elsif($_ =~ /if\(x >\= 0\)/){
		$_ = "lw \$a0,52\(\$fp\)\nbge \$a0,\$zero,answer"
	}elsif($_ =~ /x \= \-x/){
		$_ = "sub \$a0,\$zero,\$a0";
	}elsif($_ =~ /printf\(\"the answer is \%d\",x\);/){
		$_ = "answer\:\nmove \$v0,\$a0\nla \$a0,VAR2\nmove \$a1,\$v0\njal printf";
	}
}
push @lines,"move \$sp,\$fp\nlw \$fp,56\(\$sp\)\nlw \$ra,60\(\$sp\)\naddiu \$sp,\$sp,64\nj \$ra\n\.end main";

open FD,">abs.s.txt" or die "can't open for writing";
print FD "$_\n" foreach @lines;
close FD;

1;
