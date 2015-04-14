#include "contiki.h"

#if SHELL
#include "shell.h"
#include "serial-shell.h"
#include "dev/serial-line.h"
#ifdef CONTIKI_TARGET_Z1
#include "dev/uart0.h"
#else
#include "dev/uart1.h"
#endif
#include "shell-6lbr.h"
#endif

#ifdef CONTIKI_TARGET_ECONOTAG
#include "maca.h"
#endif

#if WITH_TINYDTLS
#include "dtls.h"
#endif

#if WITH_DTLS_ECHO
#include "dtls-echo.h"
#endif

PROCESS(demo_6lbr_process, "6LBR Demo");

#if WEBSERVER
PROCESS_NAME(web_sense_process);
PROCESS_NAME(webserver_nogui_process);
#endif
#if UDPCLIENT
PROCESS_NAME(udp_client_process);
#endif
#if WITH_COAP
PROCESS_NAME(rest_server_example);
#endif

/*---------------------------------------------------------------------------*/
void
start_apps(void)
{
#if UDPCLIENT
  process_start(&udp_client_process, NULL);
#endif

#if WEBSERVER
  process_start(&web_sense_process, NULL);
  process_start(&webserver_nogui_process, NULL);
#endif

#if WITH_COAP
  process_start(&rest_server_example, NULL);
#endif

#if WITH_DTLS_ECHO
  process_start(&dtls_echo_server_process, NULL);
#endif
}

PROCESS_THREAD(demo_6lbr_process, ev, data)
{
  PROCESS_BEGIN();


#if WITH_TINYDTLS
  dtls_init();
#endif

#if SHELL
#ifdef CONTIKI_TARGET_Z1
  uart0_set_input(serial_line_input_byte);
#else
  uart1_set_input(serial_line_input_byte);
#endif
  serial_line_init();

  serial_shell_init();
  shell_ping_init();
  shell_6lbr_init();
#endif
#if !WITH_DELAY_IP
  start_apps();
#endif

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
