#!/usr/bin/perl

$/ = undef ;

my @bytes = split(//, <>) ;

print "const uint8_t code[] = {" ;
my $first = 1 ;
my $addr = 0 ;
foreach my $b (@bytes){
        if (! $first){
                print(",") ;
        }
        if (($addr % 16) == 0){
                printf("\n  /* PC:0x%04X */", $addr) ;
        }
        printf("  0x%02X", ord($b)) ;
        $first = 0 ;
        $addr++ ;
}
print "\n} ;\n" ;