json.extract! user, :id, :user_id, :password, :name, :grade, :registered_at, :updated_at, :deleted_at, :created_at, :updated_at
json.url restore_url(restore, format: :json)