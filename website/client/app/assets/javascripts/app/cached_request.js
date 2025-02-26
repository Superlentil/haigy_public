modulejs.define("app/cached_request", [
  "alerter",
  "window",
  "jquery",
  "lib/cached_request",
  "app/constant",
  "app/cookie",
  "app/cache",
  "app/utility"
], function(alerter, window, $, cachedRequest, constant, cookie, cache, utility) {
  "use strict";


  var haigyClientCachedRequest = new cachedRequest({
    tokenHandler: cookie.tokenHandler,
    responseHeaderTokenAttribute: constant.session.RESPONSE_HEADER_TOKEN_ATTRIBUTE,
    actionBeforeRequest: function() {
      var token = cookie.tokenHandler.getToken();
      if (token) {
        if (cookie.getCookieTimestamp() === cache.cookieTimestamp.get()) {
          utility.setTokenInAjaxRequest(token);
        } else {
          alerter("You might have made some changes in other place. The page is going to be refreshed.");
          window.location.reload();
          throw "Refresh the page.";
        }
      } else {
        utility.setTokenInAjaxRequest(constant.session.GUEST_TOKEN);
      }
    }
  });


  return haigyClientCachedRequest;
});