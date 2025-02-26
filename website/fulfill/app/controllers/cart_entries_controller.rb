class CartEntriesController < ApplicationController

  def update
    begin
      @cartEntry = CartEntry.includes(:item).find(params[:id])
      if @cartEntry.present?
        @cartEntry.update(cartEntryParams)
      else
        renderError(HaigyManageConstant::Error::RECORD_NOT_FOUND, "Cannot find the cart entry.")
        return
      end
    rescue => error
      renderError(HaigyManageConstant::Error::UNEXPECTED_ERROR, error.message)
      return
    end
  end


  def create
    begin
      userId = params[:user_id]
      if userId.blank?
        renderError(HaigyManageConstant::Error::PARAMETERS_NOT_CORRECT, "Missing parameter: user_id")
        return
      end

      inputParams = cartEntryParams

      @item = Item.find(inputParams[:item_id])
      if @item.present?
        if inputParams[:cart_id].present?
          userCart = Cart.find(inputParams[:cart_id])
          if userCart.blank? || userCart.checked_out
            renderError(HaigyManageConstant::Error::PARAMETERS_NOT_CORRECT, "Cannot find the cart, or the cart has been checked out.")
            return
          end
        else
          userCart = Cart.where(user_id: userId, checked_out: false).first   # should have at most one unchecked out cart for each user
          unless userCart.present?
            userCart = Cart.new(
              user_id: userId,
              checked_out: false
            )
          end
        end

        if CartEntry.exists?(item_id: @item.id, cart_id: userCart.id)
          renderError(HaigyManageConstant::Error::ACTION_TOO_FREQUENTLY, "Action is too frequently.")
          return
        end

        begin
          @cartEntry = CartEntry.new(inputParams)
          @cartEntry.cart = userCart
          @cartEntry.added_by_user = false

          @cartEntry.save
        rescue => error
          renderError(HaigyManageConstant::Error::CREATE_RECORD_FAILED, ["Cannot create a cart entry. (", error.message, ")"].join(""))
          return
        end
      else
        renderError(HaigyManageConstant::Error::RECORD_NOT_FOUND, "Cannot find the item.")
        return
      end
    rescue => error
      renderError(HaigyManageConstant::Error::UNEXPECTED_ERROR, error.message)
      return
    end
  end


  def destroy
    begin
      @cartEntry = CartEntry.includes(:item).find(params[:id])
      if @cartEntry.present?
        @cartEntry.destroy
      else
        renderError(HaigyManageConstant::Error::RECORD_NOT_FOUND, "Cannot find the cart entry.")
        return
      end
    rescue => error
      renderError(HaigyManageConstant::Error::UNEXPECTED_ERROR, error.message)
      return
    end
  end


private
  def cartEntryParams
    params.require(:cart_entry).permit(
      :id,
      :cart_id,
      :item_id,
      :store_id,
      :unit_price,
      :quantity
    )
  end

end
