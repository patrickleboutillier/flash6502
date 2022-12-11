#!/usr/bin/perl


$/ = undef ;

my @bytes = split(//, <STDIN>) ;

print "uint8_t code[] = {\n" ;
foreach my $b (@bytes){
	printf("  0x%02X,\n", ord($b)) ;
}
print "}\n" ;
