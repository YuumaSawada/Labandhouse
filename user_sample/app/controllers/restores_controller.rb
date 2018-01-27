class RestoresController < ApplicationController
  before_action :set_user, only: [:show, :edit, :update]

  # GET /users
  # GET /users.json
  def index
    @dusers = User.only_deleted
  end

  # GET /users/1
  # GET /users/1.json
  def show
  end

  # GET /users/new
  def new
    @user = User.new
  end

  # GET /users/1/edit
  def edit
  end

  # POST /users
  # POST /users.json
  def create
    @duser = User.new(user_params)

    respond_to do |format|
      if @duser.save
        format.html { redirect_to @duser, notice: 'User was successfully created.' }
        format.json { render :show, status: :created, location: @duser }
      else
        format.html { render :new }
        format.json { render json: @duser.errors, status: :unprocessable_entity }
      end
    end
  end

  # PATCH/PUT /users/1
  # PATCH/PUT /users/1.json
  def update
    respond_to do |format|
      if @duser.update(user_params)
        format.html { redirect_to @duser, notice: 'User was successfully updated.' }
        format.json { render :show, status: :ok, location: @duser }
      else
        format.html { render :edit }
        format.json { render json: @duser.errors, status: :unprocessable_entity }
      end
    end
  end

  # DELETE /users/1
  # DELETE /users/1.json
  def destroy
    @duser.restore(params[:id])
  end

  private
    # Use callbacks to share common setup or constraints between actions.
    def set_user
      @duser = User.with_deleted.find(params[:id])
    end

    # Never trust parameters from the scary internet, only allow the white list through.
    def user_params
      params.require(:user).permit(:user_id, :password, :name, :grade, :registered_at, :updated_at, :deleted_at)
    end
end
