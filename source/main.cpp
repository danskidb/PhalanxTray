#include <stdio.h>
#include <string.h>
#include "defines.h"
#include "tray.h"

using namespace std;

extern struct tray tray;

static void toggle_cb(struct tray_menu *item) {
  printf("toggle cb\n");
  item->checked = !item->checked;
  tray_update(&tray);
}

static void hello_cb(struct tray_menu *item) {
  (void)item;
  printf("hello cb\n");
  if (strcmp(tray.icon, TRAY_ICON1) == 0) {
    tray.icon = TRAY_ICON2;
  } else {
    tray.icon = TRAY_ICON1;
  }
  tray_update(&tray);
}

static void quit_cb(struct tray_menu *item) {
  (void)item;
  printf("quit cb\n");
  tray_exit();
}

static void submenu_cb(struct tray_menu *item) {
  (void)item;
  printf("submenu: clicked on %s\n", item->text);
  tray_update(&tray);
}

struct tray tray = {
    .icon = TRAY_ICON1,
#if TRAY_WINAPI
    .tooltip = "Tray",
#endif
    .menu =
        (struct tray_menu[]) {
            {.text = "Hello", .cb = hello_cb},
            {.text = "Checked", .checked = 1, .checkbox = 1, .cb = toggle_cb},
            {.text = "Disabled", .disabled = 1},
            {.text = "-"},
            {.text = "SubMenu",
             .submenu =
                 (struct tray_menu[]) {
                     {.text = "FIRST", .checked = 1, .checkbox = 1, .cb = submenu_cb},
                     {.text = "SECOND",
                      .submenu =
                          (struct tray_menu[]) {
                              {.text = "THIRD",
                               .submenu =
                                   (struct tray_menu[]) {
                                       {.text = "7", .cb = submenu_cb},
                                       {.text = "-"},
                                       {.text = "8", .cb = submenu_cb},
                                       {.text = NULL}}},
                              {.text = "FOUR",
                               .submenu =
                                   (struct tray_menu[]) {
                                       {.text = "5", .cb = submenu_cb},
                                       {.text = "6", .cb = submenu_cb},
                                       {.text = NULL}}},
                              {.text = NULL}}},
                     {.text = NULL}}},
            {.text = "-"},
            {.text = "Quit", .cb = quit_cb},
            {.text = NULL}},
};

int main()
{
  if (tray_init(&tray) < 0) {
    printf("failed to create tray\n");
    return 1;
  }
  while (tray_loop(1) == 0) {
    printf("iteration\n");
  }
  return 0;
}