modulejs.define("model/cart_entry", [
  "backbone",
  "lib/backbone_cache",
  "app/utility"
], function(Backbone, backboneCache, utility) {
  "use strict";

  var cartentryModel = Backbone.Model.extend({
    urlRoot: utility.pathToUrl("/cart_entries")
  }, {
    cacher: backboneCache.generateModelCacher("cart_entry")
  });

  return cartentryModel;
});
