eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

# $Id: run_test_one_contr.pl 94040 2011-05-10 12:42:39Z mhengstmengel $
# -*- perl -*-

use lib "$ENV{'ACE_ROOT'}/bin";
use PerlACE::TestTarget;

$CIAO_ROOT = "$ENV{'CIAO_ROOT'}";
$TAO_ROOT = "$ENV{'TAO_ROOT'}";
$DANCE_ROOT = "$ENV{'DANCE_ROOT'}";

$controller_exec = "$CIAO_ROOT/examples/Display/RateGen/controller";

$tg_executor = 0;

$status = 0;

sub create_targets {
    #   executor (plan_launcher)
    $tg_executor = PerlACE::TestTarget::create_target (1) || die "Create target for executor failed\n";
    $tg_executor->AddLibPath ('../lib');
}

create_targets ();

print "Invoking the controller for first RateGen with rate = 2\n";
$controller = $tg_executor->CreateProcess ("$controller_exec", "-k file://RateGen.ior -o -r2");
$result = $controller->SpawnWaitKill (3 * $tg_executor->ProcessStopWaitInterval ());
if ($result != 0) {
    print STDERR "ERROR: The controller returned $result\n";
    $status = 1;
}

# put some delay here.
sleep (10);

# invoking the controller again to stop the rategen
print "Invoking the controller to stop the first RateGen\n";
$controller = $tg_executor->CreateProcess ("$controller_exec", "-k file://RateGen.ior -f");
$result = $controller->SpawnWaitKill ($tg_executor->ProcessStopWaitInterval ());
if ($result != 0) {
    print STDERR "ERROR: The controller returned $result\n";
    $status = 1;
}exit $status;
