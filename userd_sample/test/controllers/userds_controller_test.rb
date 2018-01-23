require 'test_helper'

class UserdsControllerTest < ActionDispatch::IntegrationTest
  setup do
    @userd = userds(:one)
  end

  test "should get index" do
    get userds_url
    assert_response :success
  end

  test "should get new" do
    get new_userd_url
    assert_response :success
  end

  test "should create userd" do
    assert_difference('Userd.count') do
      post userds_url, params: { userd: { deleted_at: @userd.deleted_at, grade: @userd.grade, name: @userd.name, password: @userd.password, registered_at: @userd.registered_at, updated_at: @userd.updated_at } }
    end

    assert_redirected_to userd_url(Userd.last)
  end

  test "should show userd" do
    get userd_url(@userd)
    assert_response :success
  end

  test "should get edit" do
    get edit_userd_url(@userd)
    assert_response :success
  end

  test "should update userd" do
    patch userd_url(@userd), params: { userd: { deleted_at: @userd.deleted_at, grade: @userd.grade, name: @userd.name, password: @userd.password, registered_at: @userd.registered_at, updated_at: @userd.updated_at } }
    assert_redirected_to userd_url(@userd)
  end

  test "should destroy userd" do
    assert_difference('Userd.count', -1) do
      delete userd_url(@userd)
    end

    assert_redirected_to userds_url
  end
end
