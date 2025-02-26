class ServiceArea < ActiveRecord::Base
  has_many :stores, dependent: :destroy
  has_many :servable_zip_codes, dependent: :destroy


  geocoded_by :office_address do |obj, results|
    if geoResult = results.first
      obj.latitude = geoResult.latitude
      obj.longitude = geoResult.longitude

      obj.formatted_address = geoResult.address
      obj.city = geoResult.city

      position = obj.formatted_address.rindex(", " + (obj.city || ""))
      if position && position > 0
        obj.street_address = obj.formatted_address[0..(position - 1)]
      else
        obj.street_address = obj.formatted_address
      end

      obj.state = geoResult.state
      obj.state_code = geoResult.state_code
      obj.postal_code = geoResult.postal_code
      obj.country = geoResult.country
      obj.country_code = geoResult.country_code
      obj.google_place_id = geoResult.data["place_id"]

      obj.geocoding_status = true
    else
      obj.geocoding_status = false
    end
  end

  # auto-fetch coordinates
  after_validation :geocode, if: ->(obj){obj.office_address.present? and obj.office_address_changed?}
end
