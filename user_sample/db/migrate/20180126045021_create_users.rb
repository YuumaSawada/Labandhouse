class CreateUsers < ActiveRecord::Migration[5.1]
  def change
    create_table :users do |t|
      t.string :user_id
      t.string :password
      t.string :name
      t.string :grade
      t.timestamp :registered_at
      t.timestamp :updated_at
      t.timestamp :deleted_at

      t.timestamps
    end
  end
end
