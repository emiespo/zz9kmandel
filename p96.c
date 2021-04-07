#include <cybergraphx/cybergraphics.h>

#include <proto/Picasso96.h>
#include <proto/cybergraphics.h>
#include <proto/graphics.h>

#include "p96.h"

/**
 * Returns the address of the screen bitmap and its RGB format.
 * 
 * @param zz9kScreen    Screen* pointer
 * @param rgbFormat     pointer to a ULONG where the format will be stored
 */
APTR getBitmapRGBFormat(struct Screen* zz9kScreen, ULONG* rbgFormat) {
  APTR bitmapAddress; 
  APTR lock = LockBitMapTags(&zz9kScreen->BitMap, LBMI_BASEADDRESS, (ULONG)&bitmapAddress, TAG_DONE);

  if (lock) {
    *rbgFormat = p96GetBitMapAttr(&zz9kScreen->BitMap, P96BMA_RGBFORMAT);
    UnLockBitMap(lock);
  } else {
    bitmapAddress = zz9kScreen->BitMap.Planes[0]; // fallback
  }
  return bitmapAddress;
}