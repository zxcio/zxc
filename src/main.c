/*
 * This file is part of zxc and is licensed under the MIT License
 *
 * Copyright (c) 2020 Mark Olsson <mark@markolsson.se>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <libserialport.h>
#include <stdio.h>

int main(
  int argc,
  char** argv
)
{
  struct sp_port** port_list;
  enum sp_return result = sp_list_ports(&port_list);

  if (result != SP_OK) {
    printf("sp_list_ports() failed!\n");
    return -1;
  }

  for (int i = 0; port_list[i] != NULL; i++) {
    struct sp_port* port = port_list[i];
    int port_vid, port_pid;
    sp_get_port_usb_vid_pid(port, &port_vid, &port_pid);

    char* port_name = sp_get_port_name(port);
    char* port_description = sp_get_port_description(port);
    char* port_serial_number = sp_get_port_usb_serial(port);
    if (port_vid != 0) {
      printf(
        "[%s] %s VID:PID=%04x:%04x Serial: %s\n",
        port_name,
        port_description,
        port_vid,
        port_pid,
        port_serial_number
      );
    }
  }
  sp_free_port_list(port_list);

  return 0;
}
