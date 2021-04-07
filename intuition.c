#include "intuition.h"

/**
 * Adapted from the ZZ900 sdk
 * https://source.mntmn.com/MNT/zz9000-sdk/src/branch/master/zz9k-loader/zz9k.c
 * 
 */

/**
 * Opens a screen using the screenmode selector.
 * @param title       Title for your intuition screen
 */
struct Screen* openScreen(const char* title) {

  // Ask the user
  struct ScreenModeRequester* aslRequester;
  aslRequester = AllocAslRequest(ASL_ScreenModeRequest, TAG_DONE);

  if (!aslRequester) {
    return NULL;
  }

  // TODO: add a filtering function for ZZ9K modes
  BOOL aslSuccess = AslRequestTags(aslRequester, ASLSM_MinDepth, 24, TAG_DONE);
  ULONG displayId = aslRequester->sm_DisplayID;

  FreeAslRequest(aslRequester);

  if (!aslSuccess || displayId == (ULONG)INVALID_ID) {
      return NULL;
  }

  return OpenScreenTags(NULL, // TagList
                            SA_Title, (ULONG)title,
                            SA_DisplayID, displayId,
                            SA_Depth, 24,
                            TAG_DONE);
}

/**
 * Simple wrapper around system CloseScreen()
 * @param screen  pointer to an intuition screen
 */
void closeScreen(struct Screen* screen) {
  if (screen) {
    CloseScreen(screen);
  }
}