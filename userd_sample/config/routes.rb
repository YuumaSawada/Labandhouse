Rails.application.routes.draw do
  resources :userds
  get '/userds/:id(.:format)' => 'userds#restore1',as: 'restore_deleted'
  post '/userds(.:format)' => 'userds#create1'

  # For details on the DSL available within this file, see http://guides.rubyonrails.org/routing.html
end
